#include "compiling.hxx"

namespace ltn::c::compile {
	ExprCode expression(const ast::Expression & expr, CompilerInfo & info) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile::binary(*binary, info);
		}
		return { "...\n", false, false, type::Type(type::TVoid) };
	}
}