#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		struct UnaryOp {
			stx::fx_ptr<type::Type(const type::Type &)> deduce;
			inst::Inst for_any;
			inst::Inst for_int;
			inst::Inst for_float;
		};



		const UnaryOp neg {
			.deduce = type::deduce_neg,
			.for_any = inst::neg(),
			.for_int = inst::neg(),
			.for_float = inst::neg(),
		};



		const UnaryOp n0t {
			.deduce = type::deduce_not,
			.for_any = inst::n0t(),
			.for_int = inst::n0t(),
			.for_float = inst::n0t(),
		};



		const UnaryOp bit_not {
			.deduce = type::deduce_bitnot,
			.for_any = inst::bit_not(),
			.for_int = inst::bit_not(),
			.for_float = inst::bit_not(),
		};



		const UnaryOp deref {
			.deduce = type::deduce_deref,
			.for_any = inst::deref(),
			.for_int = inst::deref(),
			.for_float = inst::deref(),
		};



		sst::expr_ptr analyze_null_test(
			const ast::Expression & expr,
			CompilerInfo & info,
			Scope & scope) {
			
			const auto code = analyze_expression(expr, info, scope);
			InstructionBuffer buf;
			buf << code.code;
			buf << inst::null();
			buf << inst::ueql();
			return sst::expr_ptr{ 
				.code = buf,
				.deduced_type = type::deduce_nulltest(code.deduced_type),
			};
		}



		inst::Inst pick_instruction(
			const type::Type & x,
			const UnaryOp & op) {
			if(type::is_int(x)) {
				return op.for_int;
			}  
			if(type::is_float(x)) { 
				return op.for_float;
			}
			return op.for_any;
		}



		sst::expr_ptr unary(
			const ast::expr_ptr & x,
			const UnaryOp & op) {
			InstructionBuffer buf;
			const auto type = op.deduce(x.deduced_type);
			buf << x.code;
			buf << pick_instruction(x.deduced_type, op);
			return { 
				.code = buf,
				.deduced_type = type,
			};
		}
	}


	sst::expr_ptr analyze_expr(
		const ast::Unary & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		using Op = sst::Unary::Type;
		const auto & inner = *expr.expression;
		const auto x = analyze_expression(inner, info, scope);
		
		switch (expr.type) {
			case Op::NEG:    return unary(x, neg);
			case Op::NOT:    return unary(x, n0t);
			case Op::NUL:    return analyze_null_test(inner, info, scope);
			case Op::BITNOT: return unary(x, bit_not);
			case Op::DEREF:  return unary(x, deref);
		}

		throw CompilerError{"Unknown unary expression", expr.location};
	}
}