#include "compile.hxx"
#include <string_view>
#include <limits>
#include "litan_compiler/sst/expr/Literal.hxx"


namespace ltn::c {
	namespace {
		inst::Inst pick_int_inst(std::int64_t value) {
			if(value == 0) {
				return inst::newi_const_0();
			}
			if(value == 1) {
				return inst::newi_const_1();
			}
			if(value == 2) {
				return inst::newi_const_2();
			}
			if(std::in_range<std::int8_t>(value)) {
				return inst::newi_small(static_cast<std::int8_t>(value));
			}
			return inst::newi(value);
		}
	}

	// compiles int literal
	InstructionBuffer compile_expr(const sst::expr::Integer & expr) {
		InstructionBuffer buf;
		buf << pick_int_inst(expr.value);
		return buf;
	}



	// compiles float literal
	InstructionBuffer compile_expr(const sst::expr::Float & expr) {
		InstructionBuffer buf;
		buf << inst::newf(expr.value);
		return buf;
	}



	// compiles bool literal
	InstructionBuffer compile_expr(const sst::expr::Bool & expr) {
		InstructionBuffer buf;
		if(expr.value) {
			buf << inst::bool_true();
		}
		else {
			buf << inst::bool_false();
		}
		return buf;
	}



	// compiles null literal
	InstructionBuffer compile_expr(const sst::expr::Null &) {
		InstructionBuffer buf;
		buf << inst::null();
		return buf;
	}




	// compiles string literal
	InstructionBuffer compile_expr(const sst::expr::String & expr) {
		InstructionBuffer buf;
		buf << inst::newstr(expr.value);
		return buf;
	}
}