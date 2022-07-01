#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles array literal
	ExprCode compile_array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		for(const auto & elem : array.elements) {
			buf << compile_expression(*elem, info, scope).code;
		}
		buf << ltn::inst::Newarr { array.elements.size() };
		return ExprCode{ buf };
	}
}