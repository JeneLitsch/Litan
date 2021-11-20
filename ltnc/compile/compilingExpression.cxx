#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		ExprCode assign(const ast::Assign & expr, CompilerInfo & info, Scope & scope) {
			const auto l = compile::expression(*expr.l, info, scope);
			const auto r = compile::expression(*expr.r, info, scope);
			if(!l.assignable) {
				throw CompilerError{"Left side must be assignable", expr.debugInfo.line};
			}
			std::stringstream ss;
			ss << r.code;
			ss << l.code;
			ss << inst::write;
			ss << inst::null;
			return ExprCode{ss.str(), false, false};
		}
	}

	ExprCode expression(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		if(auto binary = as<ast::Binary>(expr)) {
			return compile::binary(*binary, info, scope);
		}
		if(auto unary = as<ast::Unary>(expr)) {
			return compile::unary(*unary, info, scope);
		}
		if(auto primary = as<ast::Primary>(expr)) {
			return compile::primary(*primary, info, scope);
		}
		if(auto assing = as<ast::Assign>(expr)) {
			return compile::assign(*assing, info, scope);
		}
		return { "...EXPR\n", false, false };
	}
}