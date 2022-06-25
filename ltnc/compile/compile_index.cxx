#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles index read operation
	ExprCode index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
		const auto arr = expression(*index.expression, info, scope);
		const auto idx = expression(*index.index, info, scope);
		
		InstructionBuffer buf;
		
		buf	
			<< arr.code
			<< idx.code
			<< ltn::inst::At{};

		return ExprCode{ buf };
	}
}