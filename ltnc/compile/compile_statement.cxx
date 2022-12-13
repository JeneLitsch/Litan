#include "compile.hxx"
namespace ltn::c {
	StmtResult compile_stmt(
		const sst::StatementExpression & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto code = compile_expression(*stmt.expression, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << inst::scrap();
		return { buf, 0 };
	}


	StmtResult compile_stmt(
		const sst::DoNothing & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return StmtResult{{}, 0};
	}



	StmtResult compile_statement(
		const sst::Statement & stmt,
		CompilerInfo & info,
		Scope & scope) {
		
		return sst::visit_statement(stmt, [&] (const auto & s) {
			return compile_stmt(s, info, scope);
		});
	}
}