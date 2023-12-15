#include "compile.hxx"
#include <iostream>
#include "ltnc/sst/stmt/Return.hxx"
#include "ltnc/sst/stmt/Yield.hxx"

namespace ltn::c {
	// compiles -> return...;
	InstructionBuffer compile_stmt(const sst::stmt::Return & ret) {
		InstructionBuffer buf;
		if(ret.expr) {
			buf << compile_expression(*ret.expr);
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