#include "compile.hxx"
#include <sstream>
namespace ltn::c {
	InstructionBuffer compile_expr(const sst::GlobalVar & read) {		
		InstructionBuffer buf;
		buf << inst::global_read(read.addr);
		return buf;
	}



	InstructionBuffer compile_write_global(const sst::GlobalVar & write) {
		InstructionBuffer buf;
		buf << inst::global_write(write.addr);
		return buf;
	}



	InstructionBuffer compile_write_define(const sst::Var & def) {

		InstructionBuffer buf;
		buf << inst::global_write(def.addr);
		return buf;
	}
}