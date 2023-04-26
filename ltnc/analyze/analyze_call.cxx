#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include <string_view>
#include "conversion.hxx"

namespace ltn::c {

	namespace {
		struct ParamResult {
			sst::expr_ptr expr;
			std::optional<std::pair<std::string, type::Type>> deduced_type;
		};

		ParamResult analyze_parameter(
			const ast::Parameter::Infered & infered,
			sst::expr_ptr arg,
			Scope & scope,
			const ArgumentLocation & loc) {

			auto deduced_types = std::make_pair(infered.name, arg->type);
			
			return ParamResult{
				.expr = std::move(arg),
				.deduced_type = deduced_types,
			};
		}



		ParamResult analyze_parameter(
			const type::IncompleteType & type,
			sst::expr_ptr arg,
			Scope & scope,
			const ArgumentLocation & loc) {
				
			const auto param_type = instantiate_type(type, scope);
			auto converted = conversion_on_pass(std::move(arg), param_type, loc);
			return ParamResult{
				.expr = std::move(converted),
				.deduced_type = std::nullopt,
			};
		}



		auto analyze_arguments(
			const ast::Call & call,
			const ast::Functional & fx,
			Scope & scope) {
			
			std::vector<sst::expr_ptr> arguments;
			std::map<std::string, type::Type> deduced_param_types;
			for(std::size_t i = 0; i < call.arguments.size(); ++i) {
				const ArgumentLocation location = {ast::location(call), i};
				auto & argument = call.arguments[i];
				auto & parameter = fx.parameters[i];
				auto [arg, deduced_type] = std::visit([&] (auto & t) {
					auto arg = analyze_expression(*argument, scope);
					return analyze_parameter(t, std::move(arg), scope, location);
				}, parameter.type); 
				arguments.push_back(std::move(arg));
				if(deduced_type) {
					deduced_param_types.insert(*deduced_type);
				}
			}

			return std::make_tuple(std::move(arguments), deduced_param_types);
		}



		void guard_const(const ast::Call & call, const ast::Functional & fx, const Scope & scope) {
			if(scope.is_const() && !fx.is_const) {
				throw const_call_violation(call);
			}
		}



		bool is_inner_namespace(
			const Namespace & call_ns,
			const Namespace & fx_ns) {
			if(fx_ns.size() > call_ns.size()) return false;
			for(std::size_t i = 0; i < fx_ns.size(); i++) {
				if(call_ns[i] != fx_ns[i]) {
					return false;
				}
			}
			return true;
		}



		void guard_private(
			const ast::Functional & fx,
			const Namespace & call_ns,
			const ast::Call & call) {
			if(fx.is_private && !is_inner_namespace(call_ns, fx.namespaze)) {
				throw private_call_violation(call);
			}
		}



		sst::expr_ptr do_invoke(const ast::Call & call, Scope & scope) {

			auto expr = analyze_expression(*call.function_ptr, scope);
			auto arguments = analyze_all_expressions(call.arguments, scope);
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
			Scope & scope) {

			auto & context = scope.get_context();
			
			guard_private(fx, scope.get_namespace(), call);
			guard_const(call, fx, scope);

			auto [arguments, infered_types] = analyze_arguments(call, fx, scope);
			MinorScope dummy_scope{&scope};
			dummy_scope.inherit_types(infered_types);
			auto return_type = instantiate_type(fx.return_type, dummy_scope);
			auto fx_label = make_function_label(fx);
			
			auto sst_call = std::make_unique<sst::Call>(
				std::move(fx_label),
				std::move(arguments),
				std::move(return_type)
			);

			context.fx_queue.stage_function(fx, infered_types);
			return sst_call;
		}
	}



	// compiles function call fx(...)
	sst::expr_ptr analyze_expr(const ast::Call & call, Scope & scope) {
	
		const auto * var = as<ast::Var>(*call.function_ptr);
		if(var) {
			if(var->namespaze.empty()) {
				const auto * local = scope.resolve(var->name, location(*var));
				if(local) {
					return do_invoke(call, scope);
				}
			}

			auto & context = scope.get_context();

			const auto * fx = context.fx_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze,
				call.arguments.size()
			);

			if(fx) {
				return do_call_function(call, *fx, scope);
			}

			const auto * def = context.definition_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze
			);

			if(def) {
				return do_invoke(call, scope);
			}

			const auto * glob = context.global_table.resolve(
				var->name,
				scope.get_namespace(),
				var->namespaze
			);

			if(glob) {
				return do_invoke(call, scope);
			}


			throw undefined_function(*var);
		}

		return do_invoke(call, scope);
	}



	sst::expr_ptr analyze_expr(const ast::InvokeMember & invoke, Scope & scope) {
		auto & context = scope.get_context();
		
		auto expr = analyze_expression(*invoke.object, scope);
		auto arguments = analyze_all_expressions(invoke.arguments, scope);
		const auto type = type::deduce_invokation(expr->type);
		const auto id = context.member_table.get_id(invoke.member_name);

		return std::make_unique<sst::InvokeMember>(
			std::move(expr),
			id,
			std::move(arguments),
			type
		);
	}
}