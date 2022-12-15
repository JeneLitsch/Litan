#include "compile.hxx"
#include <iostream>

namespace ltn::c {
	// compiles -> return...;
	InstructionBuffer compile_stmt(const sst::Return & ret) {
		InstructionBuffer buf;
		if(ret.expression) {
			buf << compile_expression(*ret.expression);
		}
		else {
			buf << inst::null();
		}

		// For returns from iife
		if(ret.overide_label) {
			buf << inst::jump(*ret.overide_label);
		}
		else {
			buf << inst::retvrn();
		}
		return buf;
	}
}