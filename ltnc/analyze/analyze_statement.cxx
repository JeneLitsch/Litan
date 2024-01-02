#include "analyze.hxx"
#include "ltnc/ast/stmt/StatementExpression.hxx"
#include "ltnc/ast/stmt/Yield.hxx"
#include "ltnc/sst/stmt/NoOp.hxx"
#include "ltnc/sst/stmt/Assign.hxx"
#include "ltnc/sst/bind/Discard.hxx"
#include "ltnc/sst/stmt/Yield.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::StatementExpression & stmt, Scope & scope) {
		
		auto expr = analyze_expression(*stmt.expr, scope);
		return sst::stmt::assign(sst::bind::discard(), std::move(expr));
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::NoOp &, Scope &) {
		return sst::stmt::no_op();
	}



	sst::stmt_ptr analyze_statement(const ast::stmt::Statement & stmt, Scope & scope) {
		
		return ast::stmt::visit<sst::stmt_ptr>(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, scope);
		});
	}
}