#include "compile.hxx"

namespace ltn::c::compile {

	ExprCode negate(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::neg;
		return ExprCode{ss.str() };
	}



	ExprCode notigate (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::n0t;
		return ExprCode{ss.str() };
	}


	ExprCode null_test (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		std::stringstream ss;
		ss << code.code;
		ss << inst::null;
		ss << inst::ueql;
		return ExprCode{ss.str() };
	}
	


	ExprCode unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		using UT = ast::Unary::Type;
		const auto & inner = *expr.expression;
		
		switch (expr.type) {
			case UT::NEG: return negate(inner, info, scope);
			case UT::NOT: return notigate(inner, info, scope);
			case UT::NUL: return null_test(inner, info, scope);
		}

		throw CompilerError{"Unknown unary expression", expr.location};
	}
}