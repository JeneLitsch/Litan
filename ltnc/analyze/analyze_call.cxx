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
		return CompilerError { ss.str(), location(node) };
	}



	namespace {
		std::vector<sst::expr_ptr> analyze_arguments(
			const ast::Call & call,
			const ast::Functional & fx,
			Context & context,
			Scope & scope) {
			
			std::vector<sst::expr_ptr> arguments;
			for(std::size_t i = 0; i < call.arguments.size(); ++i) {
				const ArgumentLocation location = {ast::location(call), i};
				auto & argument = call.arguments[i];
				auto & parameter = fx.parameters[i];
				const auto param_type = instantiate_type(parameter.type, scope);
				auto arg_raw = analyze_expression(*argument, context, scope);
				auto arg_full = conversion_on_pass(std::move(arg_raw), param_type, location);
				arguments.push_back(std::move(arg_full));
			}

			return arguments;
		}



		sst::expr_ptr do_call(
			const ast::Call & call,
			const ast::Functional & fx,
			Context & context,
			Scope & scope,
			const std::optional<Label> id_override = std::nullopt) {

			guard_private(fx, scope.get_namespace(), location(call));
			
			if(scope.is_const() && !fx.is_const) throw CompilerError {
				"Cannot call non-const function from a const functions",
				location(call)
			};

			auto arguments = analyze_arguments(call, fx, context, scope);
			auto return_type = instantiate_type(fx.return_type, scope);
			auto fx_label = make_function_label(
				fx.namespaze,
				fx.name,
				fx.parameters.size()
			);
			auto label = id_override.value_or(std::move(fx_label));
			return std::make_unique<sst::Call>(
				std::move(label),
				std::move(arguments),
				std::move(return_type)
			);
		}



		sst::expr_ptr do_invoke(
			const ast::Call & call,
			Context & context,
			Scope & scope) {

			auto expr = analyze_expression(*call.function_ptr, context, scope);

			std::vector<sst::expr_ptr> arguments;
			for(const auto & param : call.arguments) {
				arguments.push_back(analyze_expression(*param, context, scope));
			}

			const auto type = type::deduce_invokation(expr->type);
			return std::make_unique<sst::Invoke>(
				std::move(expr),
				std::move(arguments),
				type
			);
		}



		sst::expr_ptr do_call_function(
			const ast::Call & call,
			const ast::Functional & fx,
			Context & context,
			Scope & scope) {
			
			context.fx_queue.stage_function(fx);
			return do_call(call, fx, context, scope);
		}



		sst::expr_ptr do_call_template(
			const ast::Call & call,
			const ast::Var & var,
			Context & context,
			Scope & scope) {
			
			const auto tmpl = get_template(
				var.name,
				var.namespaze,
				call.arguments.size(),
				call.template_arguments.size(),
				location(var),
				context,
				scope
			);

			const auto arguments = stx::fx::mapped(instantiate_type)(
				call.template_arguments,
				scope
			);

			context.fx_queue.stage_template(*tmpl, arguments);
			const auto label = make_template_label(tmpl, arguments);
			MinorScope inner_scope(&scope);

			add_template_args(
				inner_scope,
				tmpl->template_parameters,
				call.template_arguments
			);
			
			return do_call(call, *tmpl->fx, context, inner_scope, label);
		}
	}



	// compiles function call fx(...)
	sst::expr_ptr analyze_expr(
		const ast::Call & call,
		Context & context,
		Scope & scope) {
	
		const auto * var = as<ast::Var>(*call.function_ptr);
		if(var) {
			if(!call.template_arguments.empty()) {
				return do_call_template(call, *var, context, scope);
			}

			if(var->namespaze.empty()) {
				const auto * local = scope.resolve(var->name, location(*var));
				if(local) {
					return do_invoke(call, context, scope);
				}
			}

			const auto * fx = context.fx_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze,
				call.arguments.size()
			);

			if(fx) {
				return do_call_function(call, *fx, context, scope);
			}

			const auto * def = context.definition_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze
			);

			if(def) {
				return do_invoke(call, context, scope);
			}

			throw undefined_function(var->name, call);
		}

		return do_invoke(call, context, scope);
	}
}