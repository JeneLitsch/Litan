#include "compile.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::StatementExpression & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		auto expr = analyze_expression(*stmt.expression, info, scope);
		return std::make_unique<sst::StatementExpression>(0, false, std::move(expr));
	}


	sst::stmt_ptr analyze_stmt(
		const ast::DoNothing & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return std::make_unique<sst::DoNothing>(0, false);
	}



	sst::stmt_ptr  analyze_statement(
		const ast::Statement & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return ast::visit_statement(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, info, scope);
		});
	}
}