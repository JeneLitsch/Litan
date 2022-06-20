#include "compile.hxx"

namespace ltn::c::compile {

	ExprCode negate(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Neg{};
		return ExprCode{ buf };
	}



	ExprCode notigate (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Not{};
		return ExprCode{ buf };
	}


	ExprCode null_test (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Null{};
		buf << ltn::inst::Ueql{};
		return ExprCode{ buf };
	}


	ExprCode bit_not (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Bitnot{};
		return ExprCode{ buf };
	}
	


	ExprCode unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		using UT = ast::Unary::Type;
		const auto & inner = *expr.expression;
		
		switch (expr.type) {
			case UT::NEG: return negate(inner, info, scope);
			case UT::NOT: return notigate(inner, info, scope);
			case UT::NUL: return null_test(inner, info, scope);
			case UT::BITNOT: return bit_not(inner, info, scope);
		}

		throw CompilerError{"Unknown unary expression", expr.location};
	}
}