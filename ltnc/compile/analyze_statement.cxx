#include "compile.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::StatementExpression & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto code = analyze_expression(*stmt.expression, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << inst::scrap();
		return { buf, 0 };
	}


	sst::stmt_ptr analyze_stmt(
		const ast::DoNothing & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return sst::stmt_ptr {{}, 0};
	}



	sst::stmt_ptr  analyze_statement(
		const ast::Statement & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return sst::visit_statement(stmt, [&] (const auto & s) {
			return analyze_stmt(s, info, scope);
		});
	}
}