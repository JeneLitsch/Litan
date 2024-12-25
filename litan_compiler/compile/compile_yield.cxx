#include "compile.hxx"
#include <iostream>
#include "litan_compiler/sst/stmt/Return.hxx"
#include "litan_compiler/sst/stmt/Yield.hxx"

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