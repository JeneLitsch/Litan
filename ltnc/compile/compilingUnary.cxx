#include "compiling.hxx"

namespace ltn::c::compile {
	// compiles -foo
	ExprCode negate(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::neg;
		return ExprCode{ss.str(), false, code.constant };
	}

	// compiles !
	ExprCode notigate (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::n0t;
		return ExprCode{ss.str(), false, code.constant};
	}
	
	// compiles Unary
	ExprCode unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		if(expr.type == ast::Unary::Type::NEG) {
			return negate(*expr.expression, info, scope);
		}
		if(expr.type == ast::Unary::Type::NOT) {
			return notigate(*expr.expression, info, scope);
		}
		throw CompilerError{"Unknown unary expression", expr.debugInfo.line};
	}
}