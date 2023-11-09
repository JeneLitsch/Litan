#include "analyze.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Throw.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::Throw & thr0w, Scope & scope) {
		auto expr 
			= thr0w.expr
			? analyze_expression(*thr0w.expr, scope)
			: sst::expr::null();
		return sst::stmt::thr0w(std::move(expr));
	}
}