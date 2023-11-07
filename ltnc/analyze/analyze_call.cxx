#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "ltnc/sst/expr/Call.hxx"
#include "ltnc/sst/expr/Invoke.hxx"
#include "ltnc/sst/expr/InvokeMember.hxx"
#include "ltnc/sst/expr/Tuple.hxx"

namespace ltn::c {

	namespace {
		auto analyze_arguments(
			const ast::Call & call,
			const ast::Function & fx,
			Scope & scope) {
			
			std::vector<sst::expr_ptr> arguments;
			for(std::size_t i = 0; i < fx.parameters.simple.size(); ++i) {
				const ArgumentLocation location = {ast::location(call), i};
				auto & argument = call.arguments[i];
				arguments.push_back(analyze_expression(*argument, scope));
			}

			if(fx.parameters.variadic) {
				auto tuple = std::make_unique<sst::Tuple>();
				for(std::size_t i = fx.parameters.simple.size(); i < call.arguments.size(); ++i) {
					auto & argument = call.arguments[i];
					tuple->elements.push_back(analyze_expression(*argument, scope));
				}
				arguments.push_back(std::move(tuple));
			}

			return arguments;
		}



		void guard_const(const ast::Call & call, const ast::Function & fx, const Scope & scope) {
			if(scope.is_const() && !fx.is_const) {
				throw const_call_violation(call);
			}
		}



		void guard_private(
			const ast::Function & fx,
			const Namespace & call_ns,
			const ast::Call & call) {
			if(fx.is_private && !call_ns.is_inside_of(fx.namespaze)) {
				throw private_call_violation(call);
			}
		}



		sst::expr_ptr do_invoke(const ast::Call & call, Scope & scope) {

			auto expr = analyze_expression(*call.function_ptr, scope);
			auto arguments = analyze_all_expressions(call.arguments, scope);
			
			return std::make_unique<sst::Invoke>(
				std::move(expr),
				std::move(arguments)
			);
		}



		sst::expr_ptr do_call_function(
			const ast::Call & call,
			const ast::Function & fx,
			Scope & scope) {

			auto & context = scope.get_context();
			
			guard_private(fx, scope.get_namespace(), call);
			guard_const(call, fx, scope);

			auto arguments = analyze_arguments(call, fx, scope);
			MinorScope dummy_scope{&scope};
			auto fx_label = make_function_label(fx);
			
			auto sst_call = std::make_unique<sst::Call>(
				std::move(fx_label),
				std::move(arguments)
			);

			context.fx_queue.stage_function(fx);
			return sst_call;
		}
	}



	// compiles function call fx(...)
	sst::expr_ptr analyze_expr(const ast::Call & call, Scope & scope) {
	
		const auto * var = as<ast::Var>(*call.function_ptr);
		if(var) {
			if(var->namespaze.empty()) {
				if(auto local = scope.resolve_variable(var->name, location(*var))) {
					return do_invoke(call, scope);
				}
			}

			if(auto fx = scope.resolve_function(var->name, var->namespaze, call.arity(), VariadicMode::ALLOWED)) {
				return do_call_function(call, *fx, scope);
			}

			if(auto def = scope.resolve_definiton(var->name, var->namespaze)) {
				return do_invoke(call, scope);
			}

			if(auto glob = scope.resolve_global(var->name, var->namespaze)) {
				return do_invoke(call, scope);
			}

			throw undefined_function(*var);
		}

		return do_invoke(call, scope);
	}



	sst::expr_ptr analyze_expr(const ast::InvokeMember & invoke, Scope & scope) {
		auto expr = analyze_expression(*invoke.object, scope);
		auto arguments = analyze_all_expressions(invoke.arguments, scope);
		const auto id = scope.resolve_member_id(invoke.name);

		return std::make_unique<sst::InvokeMember>(
			std::move(expr),
			id,
			std::move(arguments)
		);
	}
}