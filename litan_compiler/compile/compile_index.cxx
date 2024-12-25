#include "compile.hxx"
#include <string_view>
#include "litan_compiler/sst/expr/Index.hxx"

namespace ltn::c {
	// compiles index read operation
	InstructionBuffer compile_expr(const sst::expr::Index & index) {
		const auto arr = compile_expression(*index.expr);
		const auto idx = compile_expression(*index.index);
		
		InstructionBuffer buf;
		
		buf	<< arr << idx << inst::at();

		return buf;
	}
}