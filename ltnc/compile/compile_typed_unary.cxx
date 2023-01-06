#include "compile.hxx"
#include "ltnc/compile/cast_static.hxx"
#include "ltnc/compile/cast_dynamic.hxx"
#include "ltnc/compile/copy_static.hxx"
#include "ltnc/compile/copy_dynamic.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer actual(
			const auto & actual_copy,
			const auto & copy) {
			
			const auto inner = compile_expression(*copy.expr);
			const auto outer = actual_copy(copy.expr->type, copy.target_type, {});

			InstructionBuffer buf;
			buf << inner;
			buf << outer; 

			return buf;
		}
	}



	InstructionBuffer compile_expr(const sst::TypedUnary & expr) {

		switch (expr.op) {
		case sst::TypedUnary::Op::STATIC_COPY: return actual(copy_static, expr);
		case sst::TypedUnary::Op::DYNAMIC_COPY: return actual(copy_dynamic, expr);
		case sst::TypedUnary::Op::STATIC_CAST: return actual(cast_static, expr);
		case sst::TypedUnary::Op::DYNAMIC_CAST: return actual(cast_dynamic, expr);
		default:
			break;
		}
	}
}