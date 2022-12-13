#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		struct BinOp {
			stx::fx_ptr<type::Type(const type::Type &, const type::Type &)> deduce;
			inst::Inst for_any;
			inst::Inst for_int;
			inst::Inst for_float;
		};



		const BinOp add {
			.deduce    = type::deduce_add,
			.for_any   = inst::add(),
			.for_int   = inst::add(),
			.for_float = inst::add(),
		};



		const BinOp sub {
			.deduce    = type::deduce_sub,
			.for_any   = inst::sub(),
			.for_int   = inst::sub(),
			.for_float = inst::sub(),
		};



		const BinOp mlt {
			.deduce    = type::deduce_mlt,
			.for_any   = inst::mlt(),
			.for_int   = inst::mlt(),
			.for_float = inst::mlt(),
		};



		const BinOp div {
			.deduce    = type::deduce_div,
			.for_any   = inst::div(),
			.for_int   = inst::div(),
			.for_float = inst::div(),
		};



		const BinOp mod {
			.deduce    = type::deduce_mod,
			.for_any   = inst::mod(),
			.for_int   = inst::mod(),
			.for_float = inst::mod(),
		};



		const BinOp pow {
			.deduce    = type::deduce_pow,
			.for_any   = inst::pow(),
			.for_int   = inst::pow(),
			.for_float = inst::pow(),
		};



		const BinOp lss {
			.deduce    = type::deduce_compare,
			.for_any   = inst::lt(),
			.for_int   = inst::lt(),
			.for_float = inst::lt(),
		};



		const BinOp gtr {
			.deduce    = type::deduce_compare,
			.for_any   = inst::gt(),
			.for_int   = inst::gt(),
			.for_float = inst::gt(),
		};



		const BinOp lss_eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::lt_eql(),
			.for_int   = inst::lt_eql(),
			.for_float = inst::lt_eql(),
		};



		const BinOp gtr_eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::gt_eql(),
			.for_int   = inst::gt_eql(),
			.for_float = inst::gt_eql(),
		};



		const BinOp eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::eql(),
			.for_int   = inst::eql(),
			.for_float = inst::eql(),
		};



		const BinOp ueql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::ueql(),
			.for_int   = inst::ueql(),
			.for_float = inst::ueql(),
		};



		const BinOp comp3 {
			.deduce    = type::deduce_three_way,
			.for_any   = inst::comp(),
			.for_int   = inst::comp(),
			.for_float = inst::comp(),
		};



		const BinOp bit_or {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::bit_or(),
			.for_int   = inst::bit_or(),
			.for_float = inst::bit_or(),
		};



		const BinOp bit_and {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::bit_and(),
			.for_int   = inst::bit_and(),
			.for_float = inst::bit_and(),
		};



		const BinOp bit_xor {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::bit_xor(),
			.for_int   = inst::bit_xor(),
			.for_float = inst::bit_xor(),
		};



		const BinOp shift_l {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::shift_l(),
			.for_int   = inst::shift_l(),
			.for_float = inst::shift_l(),
		};



		const BinOp shift_r {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::shift_r(),
			.for_int   = inst::shift_r(),
			.for_float = inst::shift_r(),
		};



		inst::Inst pick_instruction(
			const type::Type & l,
			const type::Type & r,
			const BinOp & op) {
			if(l == r) {
				if(type::is_int(l)) {
					return op.for_int;
				}  
				if(type::is_float(l)) { 
					return op.for_float;
				}
			}
			return op.for_any;
		}



		ExprResult bin(
			const ExprResult & l,
			const ExprResult & r,
			const BinOp & op) {
			InstructionBuffer buf;
			const auto type = op.deduce(l.deduced_type, r.deduced_type);
			buf << l.code;
			buf << r.code;
			buf << pick_instruction(l.deduced_type, r.deduced_type, op);
			return { 
				.code = buf,
				.deduced_type = type,
			};
		}



		ExprResult log_and(const ExprResult & l, const ExprResult & r) {
			const auto id = make_jump_id("AND");
			const auto end = id + "_END";
			const auto falsE = id + "FALSE";
			InstructionBuffer buf;
			buf << l.code;
			
			buf << inst::ifelse(falsE);
			buf << r.code;
			buf << inst::cast_bool();
			buf << inst::jump(end);

			buf << inst::label(falsE);
			buf << inst::bool_false();

			buf << inst::label(end);
			
			const auto type = type::deduce_logic(l.deduced_type,r.deduced_type);

			return {
				.code = buf,
				.deduced_type = type,
			};
		}



		ExprResult log_or(const ExprResult & l, const ExprResult & r) {
			const auto id = make_jump_id("OR");
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			InstructionBuffer buf;
			
			buf << l.code;
			buf << inst::n0t();
			buf << inst::ifelse(truE);
			buf << r.code;
			buf << inst::cast_bool();
			buf << inst::jump(end);

			buf << inst::label(truE);
			buf << inst::bool_true();

			buf << inst::label(end);

			const auto type = type::deduce_logic(l.deduced_type, r.deduced_type);
			
			return { 
				.code = buf,
				.deduced_type = type, 
			};
		}



		ExprResult elvis(const ExprResult & l, const ExprResult & r) {
			const auto jumpmark = make_jump_id("ELVIS");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			
			buf << l.code;
			buf << inst::duplicate();
			buf << inst::ifelse(jumpmark_else);
			buf << inst::jump(jumpmark_end);

			buf << inst::label(jumpmark_else);
			buf << inst::scrap();
			buf << r.code;
			
			buf << inst::label(jumpmark_end);
			
			const auto type = type::deduce_elvis(l.deduced_type, r.deduced_type);
			
			return {
				.code = buf,
				.deduced_type = type,
			};
		}



		ExprResult nullco(const ExprResult & l, const ExprResult & r) {
			const auto jumpmark = make_jump_id("NULLCO");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			buf << l.code;
			buf << inst::duplicate();
			buf << inst::null();
			buf << inst::ueql();
			buf << inst::ifelse(jumpmark_else);
			buf << inst::jump(jumpmark_end);

			buf << inst::label(jumpmark_else);
			buf << inst::scrap();
			buf << r.code;
			
			buf << inst::label(jumpmark_end);

			const auto type = type::deduce_nullco(l.deduced_type, r.deduced_type);

			return {
				.code = buf,
				.deduced_type = type, 
			};
		}
	}



	// compiles a binary operation
	ExprResult compile_expr(
		const sst::Binary & binary,
		CompilerInfo & info,
		Scope & scope) {
		
		using OP = ltn::c::sst::Binary::Type;
		const auto l = compile_expression(*binary.l, info, scope);
		const auto r = compile_expression(*binary.r, info, scope);
		switch (binary.type) {
			case OP::ADD:          return bin(l, r, add);
			case OP::SUB:          return bin(l, r, sub);
			case OP::MLT:          return bin(l, r, mlt);
			case OP::DIV:          return bin(l, r, div);
			case OP::MOD:          return bin(l, r, mod);
			case OP::POW:          return bin(l, r, pow);
			case OP::SMALLER:      return bin(l, r, lss);
			case OP::BIGGER:       return bin(l, r, gtr);
			case OP::SMALLEREQUAL: return bin(l, r, lss_eql);
			case OP::BIGGEREQUAL:  return bin(l, r, gtr_eql);
			case OP::EQUAL:        return bin(l, r, eql);
			case OP::UNEQUEL:      return bin(l, r, ueql);
			case OP::SPACE_SHIP:   return bin(l, r, comp3);
			case OP::SHIFT_L:      return bin(l, r, shift_l);
			case OP::SHIFT_R:      return bin(l, r, shift_r);
			case OP::BIT_AND:      return bin(l, r, bit_and);
			case OP::BIT_OR:       return bin(l, r, bit_or);
			case OP::BIT_XOR:      return bin(l, r, bit_xor);
			case OP::AND:          return log_and(l, r);
			case OP::OR:           return log_or(l, r);
			case OP::ELVIS:        return elvis(l, r);
			case OP::NULLCO:       return nullco(l, r);
		}
		throw CompilerError{"Invalid binary operation", {}};
	}
	
}