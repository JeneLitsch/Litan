#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles index read operation
	sst::expr_ptr analyze_expr(
		const ast::Index & index,
		CompilerInfo & info,
		Scope & scope) {

		const auto arr = analyze_expression(*index.expression, info, scope);
		const auto idx = analyze_expression(*index.index, info, scope);
		
		InstructionBuffer buf;
		
		buf	
			<< arr.code
			<< idx.code
			<< inst::at();

		const auto type = type::deduce_index(arr.deduced_type, idx.deduced_type);

		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = type,
		};
	}
}