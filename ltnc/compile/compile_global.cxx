#include "compile.hxx"
#include <sstream>
#include "ltnc/sst/expr/GlobalVar.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::GlobalVar & read) {		
		InstructionBuffer buf;
		buf << inst::global_read(read.address);
		return buf;
	}
}