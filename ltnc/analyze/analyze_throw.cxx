#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::Throw & thr0w, Scope & scope) {
		auto expr = thr0w.expr
			? analyze_expression(*thr0w.expr, scope)
			: std::make_unique<sst::Null>();

		return std::make_unique<sst::Throw>(std::move(expr));
	}
}