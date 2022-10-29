#include "compile.hxx"
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
		ExprResult do_call(const ast::Call & call, const ast::Functional & fx, CompilerInfo & info, Scope & scope) {

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

				buf << arg.code;
				buf << conversion_on_pass(arg.deduced_type, parameter.type, { call.location, i });
			}

			buf << inst::call(fx.id);
			
			return ExprResult{
				.code = buf,
				.deduced_type = fx.return_type,
			};
		}



		ExprResult do_invoke(const ast::Call & call, CompilerInfo & info, Scope & scope) {
			InstructionBuffer buf;

			auto fx_ptr = compile_expression(*call.function_ptr, info, scope);

			buf << fx_ptr.code;

			for(const auto & param : call.parameters) {
				buf << compile_expression(*param, info, scope).code;
			}

			buf << inst::newarr(call.parameters.size());
			buf << inst::invoke();
			
			return {
				.code = buf,
				.deduced_type = type::deduce_invokation(fx_ptr.deduced_type),
			};
		}
	}



	// compiles function call fx(...)
	ExprResult compile_call(const ast::Call & call, CompilerInfo & info, Scope & scope) {
		if(const auto * var = as<ast::Var>(*call.function_ptr)) {
			const auto * local = scope.resolve(var->name, var->location);
			if(local && var->namespaze.empty()) {
				return do_invoke(call, info, scope);
			}

			const auto * fx = info.fx_table.resolve(var->name, scope.get_namespace(), var->namespaze, call.parameters.size());
			if(fx) {
				return do_call(call, *fx, info, scope);
			}

			const auto * def = info.definition_table.resolve(var->name, scope.get_namespace(), var->namespaze);
			if(def) {
				return do_invoke(call, info, scope);
			}

			throw undefined_function(var->name, call);
		}
		else {
			return do_invoke(call, info, scope);
		}
	}
}