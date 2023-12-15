#include "compile.hxx"
#include <iostream>
#include "ltnc/sst/stmt/Return.hxx"
#include "ltnc/sst/stmt/Yield.hxx"

namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::stmt::Yield & yield) {
		InstructionBuffer buf;
		if(yield.expr) {
			buf << compile_expression(*yield.expr);
		}
		else {
			buf << inst::null();
		}

		buf << inst::yield();
		return buf;
	}
}