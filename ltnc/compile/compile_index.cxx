#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles index read operation
	ExprResult compile_index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
		const auto arr = compile_expression(*index.expression, info, scope);
		const auto idx = compile_expression(*index.index, info, scope);
		
		InstructionBuffer buf;
		
		buf	
			<< arr.code
			<< idx.code
			<< inst::at();

		return ExprResult{ 
			.code = buf,
			.deduced_type = type::deduce_index(arr.deduced_type, idx.deduced_type)
		};
	}
}