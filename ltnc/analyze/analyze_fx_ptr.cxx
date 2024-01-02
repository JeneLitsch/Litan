#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "stdxx/iife.hxx"
#include <string_view>
#include "ltnc/ast/expr/FxPointer.hxx"
#include "ltnc/sst/expr/FxPointer.hxx"

namespace ltn::c {

	sst::expr_ptr analyze_expr(const ast::expr::FxPointer & fx_ptr, Scope & scope) {
		const auto fx = scope.resolve_function(
			fx_ptr.name,
			fx_ptr.namespaze,
			fx_ptr.arity(),
			fx_ptr.is_variadic ? VariadicMode::EXACT : VariadicMode::PROHIBITED
		);

		if(!fx) throw undefined_function(fx_ptr);

		scope.require_function(StagedFunction{
			.fx = *fx,
			.captures = {},
			.override_namespace = std::nullopt,
		});

		const auto label = make_function_label(*fx);

		return sst::expr::fx_pointer(label, fx->parameters.simple.size(), fx_ptr.is_variadic);
	}
}