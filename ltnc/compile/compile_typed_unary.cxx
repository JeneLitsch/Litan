#include "compile.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		ExprResult compile_copy(
			const auto & actual_copy,
			const auto & deduce_type,
			const auto & copy,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto inner = compile_expression(*copy.expr, info, scope);
			const auto outer = actual_copy(inner.deduced_type, copy.type, copy.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return ExprResult {
				.code = buf,
				.deduced_type = deduce_type(copy.type),
			};
		}
	}


	ExprResult compile_static_copy(
		const ast::TypedUnary & copy,
		CompilerInfo & info,
		Scope & scope) {

		return compile_copy(copy_static, type::deduce_cast_static, copy, info, scope);
	}



	ExprResult compile_dynamic_copy(
		const ast::TypedUnary & copy,
		CompilerInfo & info,
		Scope & scope) {

		return compile_copy(copy_dynamic, type::deduce_cast_dynamic, copy, info, scope);
	}



	ExprResult compile_static_cast(
		const ast::TypedUnary & copy,
		CompilerInfo & info,
		Scope & scope) {
		auto expr_result = compile_expression(*copy.expr, info, scope);
		return expr_result;
	}



	ExprResult compile_dynamic_cast(
		const ast::TypedUnary & copy,
		CompilerInfo & info,
		Scope & scope) {
		auto expr_result = compile_expression(*copy.expr, info, scope);
		return expr_result;
	}



	ExprResult compile_typed_unary(
		const ast::TypedUnary & expr,
		CompilerInfo & info,
		Scope & scope) {

		switch (expr.op) {
		case ast::TypedUnary::Op::STATIC_COPY:
			return compile_static_copy(expr, info, scope);
		case ast::TypedUnary::Op::DYNAMIC_COPY:
			return compile_dynamic_copy(expr, info, scope);
		case ast::TypedUnary::Op::STATIC_CAST:
			return compile_static_cast(expr, info, scope);
		case ast::TypedUnary::Op::DYNAMIC_CAST:
			return compile_dynamic_cast(expr, info, scope);
		default:
			break;
		}

	}
}