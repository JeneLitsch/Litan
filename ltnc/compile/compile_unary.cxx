#include "compile.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/sst/expr/Unary.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer compile_null_test(const sst::Expression & expr) {
			InstructionBuffer buf;
			buf << compile_expression(expr);
			buf << inst::null();
			buf << inst::ueql();
			return buf;
		}



		InstructionBuffer unary(
			const InstructionBuffer & x,
			const auto & inst) {
			InstructionBuffer buf;
			buf << x;
			buf << inst();
			return buf;
		}
	}


	InstructionBuffer compile_expr(const sst::Unary & expr) {
		using Op = sst::Unary::Op;

		const auto & inner = *expr.expr;
		const auto x = compile_expression(inner);
		
		switch (expr.op) {
			case Op::NEG:    return unary(x, inst::neg);
			case Op::NOT:    return unary(x, inst::n0t);
			case Op::NUL:    return compile_null_test(inner);
			case Op::BITNOT: return unary(x, inst::bit_not);
			case Op::DEREF:  return unary(x, inst::deref);
		}

		throw std::runtime_error{"Unknown unary expr"};
	}
}