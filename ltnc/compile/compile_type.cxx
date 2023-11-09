#include "compile.hxx"
#include "ltnc/sst/expr/Type.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::Type & type) {
		InstructionBuffer buf;
		buf << inst::newtype(type.type_code);
		return buf;
	}
}