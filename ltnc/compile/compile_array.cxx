#include "compile.hxx"
#include <string_view>
#include "ltnc/sst/expr/Array.hxx"
#include "ltnc/sst/expr/Tuple.hxx"

namespace ltn::c {
	// compiles array literal
	InstructionBuffer compile_expr(const sst::expr::Array & array) {
		InstructionBuffer buf;
		for(const auto & elem : array.elements) {
			buf << compile_expression(*elem);
		}
		buf << inst::newarr(array.elements.size());
		return buf;
	}



	InstructionBuffer compile_expr(const sst::expr::Tuple & array) {
		InstructionBuffer buf;
		for(const auto & elem : array.elements) {
			buf << compile_expression(*elem);
		}
		buf << inst::newtuple(array.elements.size());
		return buf;
	}
}