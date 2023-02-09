#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::InitMember & stmt) {
		InstructionBuffer buf;
		buf << inst::read_x(stmt.param_addr);
		buf << inst::read_x(stmt.object_addr);
		buf << inst::member_write(stmt.member_addr);
		return buf;
	}
}