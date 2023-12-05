#include "compile.hxx"
#include "ltnc/sst/stmt/CoReturn.hxx"

namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::stmt::CoReturn & co_retvrn) {
		InstructionBuffer buf;
		if(co_retvrn.expr) {
			buf << compile_expression(*co_retvrn.expr);
		}
		else {
			buf << inst::null();
		}

		buf << inst::co_retvrn();
		return buf;
	}
}