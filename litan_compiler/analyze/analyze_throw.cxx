#include "analyze.hxx"
#include "litan_compiler/ast/stmt/Throw.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/stmt/Throw.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::Throw & thr0w, Scope & scope) {
		auto expr 
			= thr0w.expr
			? analyze_expression(*thr0w.expr, scope)
			: sst::expr::null();
		return sst::stmt::thr0w(std::move(expr));
	}
}