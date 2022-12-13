#include "compile.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "conversion.hxx"

namespace ltn::c {
	CompilerError undefined_function(
		const std::string_view & name,
		const sst::Node & node) {
		std::stringstream ss;
		ss << "Function " << name << " is not defined";
		return CompilerError { ss.str(), node.location };
	}



	namespace {
		ExprResult do_call(
			const sst::Call & call,
			const sst::Functional & fx,
			CompilerInfo & info,
			Scope & scope,
			const std::optional<std::string> id_override = std::nullopt) {

			guard_private(fx, scope.get_namespace(), call.location);
			
			if(scope.is_const() && !fx.c0nst) {
				throw CompilerError {
					"Cannot call non-const function from a const functions",
					call.location};
			}

			InstructionBuffer buf;

			for(std::size_t i = 0; i < call.parameters.size(); ++i) {
				auto & arg_expr = call.parameters[i];
				auto & parameter = fx.parameters[i];
				auto arg = compile_expression(*arg_expr, info, scope);

				const auto expr_type = arg.deduced_type;
				const auto param_type = instantiate_type(parameter.type, scope);

				buf << arg.code;
				buf << conversion_on_pass(expr_type, param_type, {call.location,i});
			}

			buf << inst::call(id_override.value_or(fx.id));

			const auto return_type = instantiate_type(fx.return_type, scope);
			
			return ExprResult{
				.code = buf,
				.deduced_type = return_type,
			};
		}



		ExprResult do_invoke(const sst::Call & call, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;

			auto fx_ptr = compile_expression(*call.function_ptr, info, scope);

			buf << fx_ptr.code;

			for(const auto & param : call.parameters) {
				buf << compile_expression(*param, info, scope).code;
			}

			buf << inst::newarr(call.parameters.size());
			buf << inst::invoke();

			const auto type = type::deduce_invokation(fx_ptr.deduced_type);
			
			return {
				.code = buf,
				.deduced_type = type,
			};
		}



		ExprResult do_call_template(
			const sst::Call & call,
			const sst::Var & var,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto tmpl = get_template(
				var.name,
				var.namespaze,
				call.parameters.size(),
				call.template_args.size(),
				var.location,
				info,
				scope
			);
			const auto arguments = stx::fx::mapped(instantiate_type)(
				call.template_args,
				scope
			);
			info.fx_queue.stage_template(*tmpl, arguments);
			const auto id = make_template_id(*tmpl->fx, arguments);
			MinorScope inner_scope(&scope);
			add_template_args(
				inner_scope,
				tmpl->template_parameters,
				call.template_args);
			return do_call(call, *tmpl->fx, info, inner_scope, id);
		}
	}



	// compiles function call fx(...)
	ExprResult compile_expr(const sst::Call & call, CompilerInfo & info, Scope & scope) {
		const auto * var = as<sst::Var>(*call.function_ptr);
		if(var) {
			if(!call.template_args.empty()) {
				return do_call_template(call, *var, info, scope);
			}
			if(var->namespaze.empty()) {
				const auto * local = scope.resolve(var->name, var->location);
				if(local) {
					return do_invoke(call, info, scope);
				}
			}

			const auto * fx = info.fx_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze,
				call.parameters.size());

			if(fx) {
				info.fx_queue.stage_function(*fx);
				return do_call(call, *fx, info, scope);
			}

			const auto * def = info.definition_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze);
			if(def) {
				return do_invoke(call, info, scope);
			}

			throw undefined_function(var->name, call);
		}

		return do_invoke(call, info, scope);
	}
}