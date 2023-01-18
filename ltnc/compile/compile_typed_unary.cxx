#include "compile.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/type/traits.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer actual(
			const auto & inst,
			const auto & copy) {
			
			const auto inner = compile_expression(*copy.expr);
			const auto outer 
				= type::is_any(copy.target_type)
				? InstructionBuffer{}
				: InstructionBuffer{inst(type::encode_type(copy.target_type))};

			InstructionBuffer buf;
			buf << inner;
			buf << outer; 

			return buf;
		}
	}



	InstructionBuffer compile_expr(const sst::TypedUnary & expr) {

		switch (expr.op) {
		case sst::TypedUnary::Op::STATIC_COPY: return actual(inst::copy, expr);
		case sst::TypedUnary::Op::DYNAMIC_COPY: return actual(inst::safe_copy, expr);
		case sst::TypedUnary::Op::STATIC_CAST: return actual(inst::cast, expr);
		case sst::TypedUnary::Op::DYNAMIC_CAST: return actual(inst::safe_cast, expr);
		case sst::TypedUnary::Op::FORCE_CAST: return actual(inst::cast, expr);
		default: throw std::runtime_error{"Invalid TypedUnary::Op"};
		}
	}
}