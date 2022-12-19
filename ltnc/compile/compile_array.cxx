#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles array literal
	InstructionBuffer compile_expr(const sst::Array & array) {
		InstructionBuffer buf;
		type::Array array_type;
		for(const auto & elem : array.elements) {
			buf << compile_expression(*elem);
		}
		buf << inst::newarr(array.elements.size());
		return buf;
	}
}