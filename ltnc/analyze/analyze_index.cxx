#include "analyze.hxx"
#include <string_view>
#include "stdxx/iife.hxx"
#include "ltnc/sst/expr/Index.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Index & index, Scope & scope) {
		auto arr = analyze_expression(*index.expr, scope);
		auto idx = analyze_expression(*index.index, scope);
		return std::make_unique<sst::Index>(
			std::move(arr),
			std::move(idx)
		);
	}
}