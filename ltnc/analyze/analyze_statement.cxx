#include "analyze.hxx"
#include "ltnc/sst/stmt/NoOp.hxx"
#include "ltnc/sst/stmt/Assign.hxx"
#include "ltnc/sst/bind/Discard.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::StatementExpression & stmt, Scope & scope) {
		
		auto expr = analyze_expression(*stmt.expr, scope);
		return sst::stmt::assign(sst::bind::discard(), std::move(expr));
	}



	sst::stmt_ptr analyze_stmt(const ast::NoOp &, Scope &) {
		return sst::stmt::no_op();
	}



	sst::stmt_ptr  analyze_statement(const ast::Statement & stmt, Scope & scope) {
		
		return ast::visit_statement(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, scope);
		});
	}
}