#include "compile.hxx"

namespace ltn::c {
	namespace {
		ExprResult compile_negate(const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
			const auto code = compile_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::neg();
			return ExprResult{ 
				.code = buf,
				.deduced_type = type::deduce_neg(code.deduced_type)
			};
		}



		ExprResult compile_notigate (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
			const auto code = compile_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::n0t();
			return ExprResult{
				.code = buf,
				.deduced_type = type::deduce_not(code.deduced_type),
			};
		}


		ExprResult compile_null_test (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
			const auto code = compile_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::null();
			buf << inst::ueql();
			return ExprResult{ 
				.code = buf,
				.deduced_type = type::deduce_nulltest(code.deduced_type),
			};
		}


		ExprResult compile_bit_not (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
			const auto code = compile_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::bit_not();
			return ExprResult{
				.code = buf,
				.deduced_type = type::deduce_bitnot(code.deduced_type),
			};
		}
		


		ExprResult compile_deref (const ast::Expression & expr, CompilerInfo & info, Scope & scope) {
			const auto code = compile_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::deref();
			return ExprResult{
				.code = buf,
				.deduced_type = type::deduce_deref(code.deduced_type),
			};
		}
	}


	ExprResult compile_expr(const ast::Unary & expr, CompilerInfo & info, Scope & scope) {
		using UT = ast::Unary::Type;
		const auto & inner = *expr.expression;
		
		switch (expr.type) {
			case UT::NEG:    return compile_negate(inner, info, scope);
			case UT::NOT:    return compile_notigate(inner, info, scope);
			case UT::NUL:    return compile_null_test(inner, info, scope);
			case UT::BITNOT: return compile_bit_not(inner, info, scope);
			case UT::DEREF:  return compile_deref(inner, info, scope);
		}

		throw CompilerError{"Unknown unary expression", expr.location};
	}
}