#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
// #include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer actual(
			const auto & actual_copy,
			const auto & copy) {
			
			const auto inner = compile_expression(*copy.expr, info, scope);
			const auto outer = actual_copy(inner.deduced_type, type, copy.location);

			InstructionBuffer buf;
			buf << inner.code;
			buf << outer; 

			return buf;
		}
	}



	InstructionBuffer compile_expr(
		const sst::TypedUnary & expr,
		CompilerInfo & info,
		Scope & scope) {

		switch (expr.op) {
		case sst::TypedUnary::Op::STATIC_COPY: return actual(copy_static, expr);
		case sst::TypedUnary::Op::DYNAMIC_COPY: return actual(copy_dynamic, expr);
		case sst::TypedUnary::Op::STATIC_CAST: return actual(cast_static, expr);
		// case sst::TypedUnary::Op::DYNAMIC_CAST: return actual(cast_dynamic, type::deduce_cast_static, expr);
		default:
			break;
		}

	}
}