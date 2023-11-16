#include "analyze.hxx"
#include <string_view>
#include "stdxx/iife.hxx"
#include "ltnc/sst/expr/Index.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Index & index, Scope & scope) {
		auto arr = analyze_expression(*index.expr, scope);
		auto idx = analyze_expression(*index.index, scope);
		return sst::expr::index(std::move(arr), std::move(idx));
	}
}