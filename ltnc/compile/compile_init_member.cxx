#include "compile.hxx"
namespace ltn::c::compile {
	StmtCode init_member(const ast::InitMember & stmt, CompilerInfo & info, Scope & scope) {
		const auto obj = scope.resolve("obj", stmt.location);
		const auto var = scope.resolve(stmt.param, stmt.location);
		const auto mem = info.member_table.get_id(stmt.member);
		
		InstructionBuffer buf;
		
		buf 
			<< ltn::inst::Readx{var.address}
			<< ltn::inst::Readx{obj.address}
			<< ltn::inst::MemberWrite{mem};
		
		return StmtCode{buf, 0, false};
	}
}