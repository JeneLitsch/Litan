#include <string_view>
#include "stdxx/functional.hxx"
#include "analyze.hxx"

#include "ltnc/ast/expr/Call.hxx"
#include "ltnc/ast/expr/InvokeMember.hxx"
#include "ltnc/ast/expr/Var.hxx"

#include "ltnc/sst/expr/Call.hxx"
#include "ltnc/sst/expr/Invoke.hxx"
#include "ltnc/sst/expr/InvokeMember.hxx"
#include "ltnc/sst/expr/Tuple.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {

	namespace {
		auto analyze_arguments(
			const ast::expr::Call & call,
			const ast::decl::Function & fx,
			Scope & scope) {
			
			std::vector<sst::expr_ptr> arguments;
			for(std::size_t i = 0; i < fx.parameters.simple.size(); ++i) {
				const ArgumentLocation location = {ast::location(call), i};
				auto & argument = call.arguments[i];
				arguments.push_back(analyze_expression(*argument, scope));
			}

			if(fx.parameters.variadic) {
				auto tuple = sst::expr::tuple();
				for(std::size_t i = fx.parameters.simple.size(); i < call.arguments.size(); ++i) {
					auto & argument = call.arguments[i];
					tuple->push_back(analyze_expression(*argument, scope));
				}
				arguments.push_back(std::move(tuple));
			}

			return arguments;
		}



		void guard_const(const ast::expr::Call & call, const ast::decl::Function & fx, const Scope & scope) {
			if(scope.is_const() && !fx.qualifiers.is_const) {
				throw const_call_violation(call);
			}
		}



		void guard_private(
			const ast::decl::Function & fx,
			const Namespace & call_ns,
			const ast::expr::Call & call) {
			if(fx.qualifiers.is_private && !call_ns.is_inside_of(fx.namespaze)) {
				throw private_call_violation(call);
			}
		}



		sst::expr_ptr do_invoke(const ast::expr::Call & call, Scope & scope) {

			auto expr = analyze_expression(*call.function_ptr, scope);
			auto arguments = stx::fx::map([&] (const auto & expr) { return analyze_expression(*expr, scope); }, call.arguments);			
			return sst::expr::invoke(std::move(expr), std::move(arguments));
		}



		sst::expr_ptr do_call_function(
			const ast::expr::Call & call,
			const ast::decl::Function & fx,
			Scope & scope) {

			guard_private(fx, scope.get_namespace(), call);
			guard_const(call, fx, scope);

			auto arguments = analyze_arguments(call, fx, scope);
			auto fx_label = make_function_label(fx);
			
			scope.require_function(fx);
			return sst::expr::call(std::move(fx_label), std::move(arguments));
		}
	}



	// compiles function call fx(...)
	sst::expr_ptr analyze_expr(const ast::expr::Call & call, Scope & scope) {
	
		const auto * var = as<ast::expr::Var>(*call.function_ptr);
		if(var) {
			if(var->namespaze.empty()) {
				if(auto local = scope.resolve_local_variable(var->name, location(*var))) {
					return do_invoke(call, scope);
				}
			}

			if(auto fx = scope.resolve_function(var->name, var->namespaze, call.arity(), VariadicMode::ALLOWED)) {
				return do_call_function(call, *fx, scope);
			}

			if(auto def = scope.resolve_definiton(var->name, var->namespaze)) {
				return do_invoke(call, scope);
			}

			if(auto glob = scope.resolve_global_variable(var->name, var->namespaze)) {
				return do_invoke(call, scope);
			}

			throw undefined_function(*var);
		}

		return do_invoke(call, scope);
	}



	sst::expr_ptr analyze_expr(const ast::expr::InvokeMember & invoke, Scope & scope) {
		auto expr = analyze_expression(*invoke.object, scope);
		auto arguments = stx::fx::map([&] (const auto & expr) { return analyze_expression(*expr, scope); }, invoke.arguments);			
		const auto id = scope.resolve_member_id(invoke.name);

		return sst::expr::invoke_member(std::move(expr), id, std::move(arguments));
	}
}