#include "compile.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::InitStruct & init) {
		InstructionBuffer buf;
		buf << inst::newstruct();
		for(const auto & [member, expr] : init.members) {
			buf << inst::duplicate();
			buf << compile_expression(*expr);
			buf << inst::swap();
			buf << inst::member_write(member);
		}
		return buf;
	}
}