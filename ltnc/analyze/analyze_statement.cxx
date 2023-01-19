#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::StatementExpression & stmt,
		Context & context,
		Scope & scope) {
		
		auto expr = analyze_expression(*stmt.expression, context, scope);
		return std::make_unique<sst::StatementExpression>(0, false, std::move(expr));
	}



	sst::stmt_ptr analyze_stmt(
		const ast::DoNothing &,
		Context &,
		Scope &) {
		
		return std::make_unique<sst::DoNothing>(0, false);
	}







	sst::stmt_ptr  analyze_statement(
		const ast::Statement & stmt,
		Context & context,
		Scope & scope) {
		
		return ast::visit_statement(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, context, scope);
		});
	}
}