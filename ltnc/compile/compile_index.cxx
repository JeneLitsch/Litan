#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles index read operation
	ExprCode compile_index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
		const auto arr = compile_expression(*index.expression, info, scope);
		const auto idx = compile_expression(*index.index, info, scope);
		
		InstructionBuffer buf;
		
		buf	
			<< arr.code
			<< idx.code
			<< ltn::inst::At{};

		return ExprCode{ buf };
	}
}