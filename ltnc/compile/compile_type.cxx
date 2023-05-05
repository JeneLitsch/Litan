#include "compile.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::Type & type) {
		InstructionBuffer buf;
		buf << inst::newstr(type.type_code);
		return buf;
	}
}