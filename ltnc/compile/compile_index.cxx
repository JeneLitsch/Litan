#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles index read operation
	InstructionBuffer compile_expr(const sst::Index & index) {
		const auto arr = compile_expression(*index.expression);
		const auto idx = compile_expression(*index.index);
		
		InstructionBuffer buf;
		
		buf	<< arr << idx << inst::at();

		return buf;
	}
}