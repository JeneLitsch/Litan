#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/memory.hxx"
#include "ltnc/ast/expr/Lambda.hxx"
#include "ltnc/sst/expr/FxPointer.hxx"
#include "ltnc/sst/expr/Var.hxx"

namespace ltn::c {
	namespace {
		auto analyze_captures(const auto & captures, auto & outer_scope) {
			auto fx = [&] (const auto & capture) {
				auto expr = analyze_expr(*capture, outer_scope);
				return stx::static_unique_cast<sst::expr::Var>(std::move(expr));
			};
			return stx::fx::map(fx, captures);
		}
	}



	sst::expr_ptr analyze_expr(const ast::expr::Lambda & lambda, Scope & outer_scope) {
		
		auto label = make_lambda_label(lambda);

		auto captures = analyze_captures(lambda.captures, outer_scope);

		outer_scope.require_function(StagedFunction{
			.fx = *lambda.fx,
			.captures = lambda.captures,
			.override_namespace = outer_scope.get_namespace(),
		});

		auto fx_ptr = sst::expr::fx_pointer(
			make_function_label(*lambda.fx),
			lambda.fx->parameters.simple.size(),
			lambda.fx->parameters.variadic.has_value()
		);

		fx_ptr->captures = std::move(captures);

		return fx_ptr;
	}
}