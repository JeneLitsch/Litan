#include "compile.hxx"

namespace ltn::c {

	ExprCode compile_negate(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = compile_expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Neg{};
		return ExprCode{ buf };
	}



	ExprCode compile_notigate (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = compile_expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Not{};
		return ExprCode{ buf };
	}


	ExprCode compile_null_test (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = compile_expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Null{};
		buf << ltn::inst::Ueql{};
		return ExprCode{ buf };
	}


	ExprCode compile_bit_not (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
		const auto code = compile_expression(expr, info, scope);
		InstructionBuffer buf;
		buf << code.code;
		buf << ltn::inst::Bitnot{};
		return ExprCode{ buf };
	}
	


	ExprCode compile_unary(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		using UT = ast::Unary::Type;
		const auto & inner = *expr.expression;
		
		switch (expr.type) {
			case UT::NEG: return compile_negate(inner, info, scope);
			case UT::NOT: return compile_notigate(inner, info, scope);
			case UT::NUL: return compile_null_test(inner, info, scope);
			case UT::BITNOT: return compile_bit_not(inner, info, scope);
		}

		throw CompilerError{"Unknown unary expression", expr.location};
	}
}