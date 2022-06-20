#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles array literal
	ExprCode array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
		InstructionBuffer buf;
		for(const auto & elem : array.elements) {
			buf << expression(*elem, info, scope).code;
		}
		buf << ltn::inst::Newarr{array.elements.size()};
		return ExprCode{ buf };
	}
}