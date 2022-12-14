#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
// #include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr actual(
			const auto & actual_copy,
			const auto & deduce_type,
			const auto & copy,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto type = instantiate_type(copy.type, scope);
			const auto inner = analyze_expression(*copy.expr, info, scope);
			const auto outer = actual_copy(inner.deduced_type, type, copy.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return sst::expr_ptr {
				.code = buf,
				.deduced_type = deduce_type(type),
			};
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::TypedUnary & expr,
		CompilerInfo & info,
		Scope & scope) {

		switch (expr.op) {
		case sst::TypedUnary::Op::STATIC_COPY:
			return actual(copy_static, type::deduce_copy_static, expr, info, scope);
		case sst::TypedUnary::Op::DYNAMIC_COPY:
			return actual(copy_dynamic, type::deduce_copy_dynamic, expr, info, scope);
		case sst::TypedUnary::Op::STATIC_CAST:
			return actual(cast_static, type::deduce_cast_static, expr, info, scope);
		// case ast::TypedUnary::Op::DYNAMIC_CAST:
			// return analyze_cast_copy(cast_dynamic, type::deduce_cast_dynamic, copy, info, scope);
		default:
			break;
		}

	}
}