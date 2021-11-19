#include "compiling.hxx"

namespace ltn::c::compile {
	ExprCode expression(const ast::Expression & expr, CompilerInfo & info) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile::binary(*binary, info);
		}
		if(auto unary = as<ast::Unary>(expr)) {
			return compile::unary(*unary, info);
		}
		if(auto primary = as<ast::Primary>(expr)) {
			return compile::primary(*primary, info);
		}
		return { "...\n", false, false };
	}
}