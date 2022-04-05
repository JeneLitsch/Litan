#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles index read operation
	ExprCode index(const ast::Index & index, CompilerInfo & info, Scope & scope) {
		const auto arr = expression(*index.expression, info, scope);
		const auto idx = expression(*index.index, info, scope);
		std::stringstream ss;
		ss	<< arr.code
			<< idx.code
			<< inst::at;
		return ExprCode{ss.str() };
	}
}