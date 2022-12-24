#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "conversion.hxx"

namespace ltn::c {
	CompilerError undefined_function(
		const std::string_view & name,
		const ast::Node & node) {
		std::stringstream ss;
		ss << "Function " << name << " is not defined";
		return CompilerError { ss.str(), node.location };
	}



	namespace {
		sst::expr_ptr do_call(
			const ast::Call & call,
			const ast::Functional & fx,
			std::vector<sst::expr_ptr> function_args,
			Context & context,
			Scope & scope,
			const std::optional<Label> id_override = std::nullopt) {

			guard_private(fx, scope.get_namespace(), call.location);
			
			if(scope.is_const() && !fx.is_const) {
				throw CompilerError {
					"Cannot call non-const function from a const functions",
					call.location};
			}

			for(std::size_t i = 0; i < call.parameters.size(); ++i) {
				auto & parameter = fx.parameters[i];
				const auto expr_type = function_args[i]->type;
				const auto param_type = instantiate_type(parameter.type, scope);
				function_args[i] = conversion_on_pass(
					std::move(function_args[i]),
					param_type,
					{call.location,i}
				);
			}

			const auto return_type = instantiate_type(fx.return_type, scope);
			const auto fx_label = make_function_label(
				fx.namespaze,
				fx.name,
				fx.parameters.size()
			);
			const auto label = id_override.value_or(fx_label);
			
			return std::make_unique<sst::Call>(
				label,
				std::move(function_args),
				return_type
			);
		}



		sst::expr_ptr do_invoke(
			const ast::Call & call,
			std::vector<sst::expr_ptr> function_args,
			Context & context,
			Scope & scope) {

			auto expr = analyze_expression(*call.function_ptr, context, scope);

			const auto type = type::deduce_invokation(expr->type);
			return std::make_unique<sst::Invoke>(
				std::move(expr),
				std::move(function_args),
				type
			);
		}



		sst::expr_ptr do_call_template(
			const ast::Call & call,
			const ast::Var & var,
			std::vector<sst::expr_ptr> function_args,
			Context & context,
			Scope & scope) {
			
			const auto tmpl = get_template(
				var.name,
				var.namespaze,
				call.parameters.size(),
				call.template_args.size(),
				var.location,
				context,
				scope
			);
			const auto template_args = stx::fx::mapped(instantiate_type)(
				call.template_args,
				scope
			);
			context.fx_queue.stage_template(*tmpl, template_args);
			const auto label = make_template_label(tmpl, template_args);
			MinorScope inner_scope(&scope);
			add_template_args(
				inner_scope,
				tmpl->template_parameters,
				call.template_args);

			return do_call(
				call,
				*tmpl->fx,
				std::move(function_args),
				context,
				inner_scope,
				label);
		}



		bool matches_strict(
			const ast::Functional & function,
			const std::vector<sst::expr_ptr> & arguments,
			const Scope & scope) {
			
			for(std::size_t i = 0; i < function.parameters.size(); ++i) {
				auto param_type = instantiate_type(
					function.parameters[i].type,
					scope
				);
				if(arguments[i]->type != param_type) {
					return false;
				}
			}

			return true;
		}



		const ast::Functional * qualify_overload(
			const ast::Overload & overload,
			const FunctionTable & fx_table,
			const std::vector<sst::expr_ptr> & arguments,
			const Scope & scope) {
			
			for(const auto & element : overload.elements) {
				auto * fx = fx_table.resolve(
					element.name,
					overload.namespaze,
					element.namespaze,
					overload.arity
				);

				if(!fx) {
					throw undefined_function(overload.name, overload);
				}

				if(matches_strict(*fx, arguments, scope)) return fx;

			}

			return nullptr;
		}
	}



	// compiles function call fx(...)
	sst::expr_ptr analyze_expr(
		const ast::Call & call,
		Context & context,
		Scope & scope) {
		
		std::vector<sst::expr_ptr> arguments;
		for(const auto & param : call.parameters) {
			arguments.push_back(analyze_expression(*param, context, scope));
		}
		const auto * var = as<ast::Var>(*call.function_ptr);
		if(var) {
			if(!call.template_args.empty()) {
				return do_call_template(call, *var, std::move(arguments), context, scope);
			}
			if(var->namespaze.empty()) {
				const auto * local = scope.resolve(var->name, var->location);
				if(local) {
					return do_invoke(call, std::move(arguments), context, scope);
				}
			}

			const auto * fx = context.fx_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze,
				call.parameters.size());

			if(fx) {
				context.fx_queue.stage_function(*fx);
				return do_call(call, *fx, std::move(arguments), context, scope);
			}

			const auto * overload = context.overload_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze,
				call.parameters.size());

			if(overload) {
				auto * ofx = qualify_overload(
					*overload,
					context.fx_table,
					arguments,
					scope
				);

				context.fx_queue.stage_function(*ofx);
				return do_call(call, *ofx, std::move(arguments), context, scope);
			}

			const auto * def = context.definition_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze);
			if(def) {
				return do_invoke(call, std::move(arguments), context, scope);
			}

			throw undefined_function(var->name, call);
		}

		return do_invoke(call, std::move(arguments), context, scope);
	}
}