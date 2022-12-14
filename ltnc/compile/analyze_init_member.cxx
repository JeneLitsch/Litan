#include "compile.hxx"
namespace ltn::c {
	sst::stmt_ptr analyze_stmt(
		const ast::InitMember & stmt,
		CompilerInfo & info,
		Scope & scope) {

		const auto obj = scope.resolve("obj", stmt.location);
		const auto var = scope.resolve(stmt.param, stmt.location);
		const auto mem = info.member_table.get_id(stmt.member);
		
		InstructionBuffer buf;
		
		buf 
			<< inst::read_x(var->address)
			<< inst::read_x(obj->address)
			<< inst::member_write(mem);
		
		return sst::stmt_ptr {buf, 0, false};
	}
}