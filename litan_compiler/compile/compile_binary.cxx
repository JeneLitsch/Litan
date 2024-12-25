#include "compile.hxx"
#include <iostream>
#include "stdxx/functional.hxx"
#include "litan_compiler/sst/expr/Binary.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer bin(
			const InstructionBuffer & l,
			const InstructionBuffer & r,
			const auto & inst) {
			InstructionBuffer buf;
			buf << l;
			buf << r;
			buf << inst();
			return buf;
		}



		InstructionBuffer log_and(const InstructionBuffer & l, const InstructionBuffer & r) {
			const auto id = make_jump_id("AND");
			const auto end = id + "_END";
			const auto falsE = id + "FALSE";
			InstructionBuffer buf;
			buf << l;
			
			buf << inst::ifelse(falsE);
			buf << r;
			buf << inst::cast_bool();
			buf << inst::jump(end);

			buf << inst::label(falsE);
			buf << inst::bool_false();

			buf << inst::label(end);
			
			return buf;
		}



		InstructionBuffer log_or(const InstructionBuffer & l, const InstructionBuffer & r) {
			const auto id = make_jump_id("OR");
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			InstructionBuffer buf;
			
			buf << l;
			buf << inst::n0t();
			buf << inst::ifelse(truE);
			buf << r;
			buf << inst::cast_bool();
			buf << inst::jump(end);

			buf << inst::label(truE);
			buf << inst::bool_true();

			buf << inst::label(end);

			return buf;
		}



		InstructionBuffer elvis(const InstructionBuffer & l, const InstructionBuffer & r) {
			const auto jumpmark = make_jump_id("ELVIS");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			
			buf << l;
			buf << inst::duplicate();
			buf << inst::ifelse(jumpmark_else);
			buf << inst::jump(jumpmark_end);

			buf << inst::label(jumpmark_else);
			buf << inst::scrap();
			buf << r;
			
			buf << inst::label(jumpmark_end);
			
			return buf;
		}



		InstructionBuffer nullco(const InstructionBuffer & l, const InstructionBuffer & r) {
			const auto jumpmark = make_jump_id("NULLCO");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			buf << l;
			buf << inst::duplicate();
			buf << inst::null();
			buf << inst::ueql();
			buf << inst::ifelse(jumpmark_else);
			buf << inst::jump(jumpmark_end);

			buf << inst::label(jumpmark_else);
			buf << inst::scrap();
			buf << r;
			
			buf << inst::label(jumpmark_end);

			return buf;

		}
	}



	// compiles a binary operation
	InstructionBuffer compile_expr(const sst::expr::Binary & binary) {
		
		using OP = ltn::c::sst::expr::Binary::Op;
		const auto l = compile_expression(*binary.l);
		const auto r = compile_expression(*binary.r);
		switch (binary.op) {
			case OP::ADD:          return bin(l, r, inst::add);
			case OP::SUB:          return bin(l, r, inst::sub);
			case OP::MLT:          return bin(l, r, inst::mlt);
			case OP::DIV:          return bin(l, r, inst::div);
			case OP::MOD:          return bin(l, r, inst::mod);
			case OP::POW:          return bin(l, r, inst::pow);
			case OP::SMALLER:      return bin(l, r, inst::lt);
			case OP::BIGGER:       return bin(l, r, inst::gt);
			case OP::SMALLEREQUAL: return bin(l, r, inst::lt_eql);
			case OP::BIGGEREQUAL:  return bin(l, r, inst::gt_eql);
			case OP::EQUAL:        return bin(l, r, inst::eql);
			case OP::UNEQUEL:      return bin(l, r, inst::ueql);
			case OP::SPACE_SHIP:   return bin(l, r, inst::comp);
			case OP::SHIFT_L:      return bin(l, r, inst::shift_l);
			case OP::SHIFT_R:      return bin(l, r, inst::shift_r);
			case OP::BIT_AND:      return bin(l, r, inst::bit_and);
			case OP::BIT_OR:       return bin(l, r, inst::bit_or);
			case OP::BIT_XOR:      return bin(l, r, inst::bit_xor);
			case OP::AND:          return log_and(l, r);
			case OP::OR:           return log_or(l, r);
			case OP::ELVIS:        return elvis(l, r);
			case OP::NULLCO:       return nullco(l, r);
		}
		throw CompilerError{"Invalid binary operation", {}};
	}
	
}