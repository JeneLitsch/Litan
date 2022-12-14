#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::StatementExpression & stmt) {
		
		const auto code = compile_expression(*stmt.expression);
		InstructionBuffer buf;
		buf << code;
		buf << inst::scrap();
		return buf;
	}


	InstructionBuffer compile_stmt(const sst::DoNothing &) {
		return {};
	}



	InstructionBuffer compile_statement(const sst::Statement & stmt) {
		return sst::visit_statement(stmt, [&] (const auto & s) {
			return compile_stmt(s);
		});
	}
}