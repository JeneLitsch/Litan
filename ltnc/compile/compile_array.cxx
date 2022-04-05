#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles array literal
	ExprCode array(const ast::Array & array, CompilerInfo & info, Scope & scope) {
		std::stringstream ss;
		for(const auto & elem : array.elements) {
			ss << expression(*elem, info, scope).code;
		}
		ss << inst::newarr(array.elements.size());
		return ExprCode{ ss.str() };
	}
}