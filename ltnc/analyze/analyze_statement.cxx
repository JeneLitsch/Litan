#include "analyze.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::StatementExpression & stmt, Scope & scope) {
		
		auto expr = analyze_expression(*stmt.expr, scope);
		return std::make_unique<sst::Assign>(
			std::make_unique<sst::NoBinding>(),
			std::move(expr)
		);
	}



	sst::stmt_ptr analyze_stmt(const ast::NoOp &, Scope &) {
		
		return std::make_unique<sst::NoOp>();
	}



	sst::stmt_ptr  analyze_statement(const ast::Statement & stmt, Scope & scope) {
		
		return ast::visit_statement(stmt, [&] (const auto & s) -> sst::stmt_ptr {
			return analyze_stmt(s, scope);
		});
	}
}