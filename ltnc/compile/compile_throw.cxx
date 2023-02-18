#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::Throw & thr0w) {
		InstructionBuffer buf;
		buf << compile_expression(*thr0w.expr);
		buf << inst::thr0w();
		return buf;
	}
}