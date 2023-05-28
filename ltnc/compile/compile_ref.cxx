#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	InstructionBuffer compile_expr(const sst::RefLocal & ref) {
		InstructionBuffer buf;
		buf << inst::newref_local(ref.address);
		return buf;
	}



	InstructionBuffer compile_expr(const sst::Deref & deref) {
		InstructionBuffer buf;
		buf << compile_expression(*deref.expr);
		buf << inst::ref_read();
		return buf;
	}
}