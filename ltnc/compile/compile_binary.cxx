#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include <iostream>
#include "stdxx/fx_ptr.hxx"

namespace ltn::c {
	namespace {
		using OP = ltn::c::ast::Binary::Type;


		struct BinOp {
			stx::fx_ptr<type::Type(const type::Type &, const type::Type &)> deduce;
			inst::Instruction for_any;
			inst::Instruction for_int;
			inst::Instruction for_float;
		};



		const BinOp add {
			.deduce    = type::deduce_add,
			.for_any   = inst::Add{},
			.for_int   = inst::Add{},
			.for_float = inst::Add{},
		};



		const BinOp sub {
			.deduce    = type::deduce_sub,
			.for_any   = inst::Sub{},
			.for_int   = inst::Sub{},
			.for_float = inst::Sub{},
		};



		const BinOp mlt {
			.deduce    = type::deduce_mlt,
			.for_any   = inst::Mlt{},
			.for_int   = inst::Mlt{},
			.for_float = inst::Mlt{},
		};



		const BinOp div {
			.deduce    = type::deduce_div,
			.for_any   = inst::Div{},
			.for_int   = inst::Div{},
			.for_float = inst::Div{},
		};



		const BinOp mod {
			.deduce    = type::deduce_mod,
			.for_any   = inst::Mod{},
			.for_int   = inst::Mod{},
			.for_float = inst::Mod{},
		};



		const BinOp pow {
			.deduce    = type::deduce_pow,
			.for_any   = inst::Pow{},
			.for_int   = inst::Pow{},
			.for_float = inst::Pow{},
		};



		const BinOp lss {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Sml{},
			.for_int   = inst::Sml{},
			.for_float = inst::Sml{},
		};



		const BinOp gtr {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Bgr{},
			.for_int   = inst::Bgr{},
			.for_float = inst::Bgr{},
		};



		const BinOp lss_eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Smleql{},
			.for_int   = inst::Smleql{},
			.for_float = inst::Smleql{},
		};



		const BinOp gtr_eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Bgreql{},
			.for_int   = inst::Bgreql{},
			.for_float = inst::Bgreql{},
		};



		const BinOp eql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Eql{},
			.for_int   = inst::Eql{},
			.for_float = inst::Eql{},
		};



		const BinOp ueql {
			.deduce    = type::deduce_compare,
			.for_any   = inst::Ueql{},
			.for_int   = inst::Ueql{},
			.for_float = inst::Ueql{},
		};



		const BinOp comp3 {
			.deduce    = type::deduce_three_way,
			.for_any   = inst::Comp{},
			.for_int   = inst::Comp{},
			.for_float = inst::Comp{},
		};



		const BinOp bit_or {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::Bitor{},
			.for_int   = inst::Bitor{},
			.for_float = inst::Bitor{},
		};



		const BinOp bit_and {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::Bitand{},
			.for_int   = inst::Bitand{},
			.for_float = inst::Bitand{},
		};



		const BinOp bit_xor {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::Bitxor{},
			.for_int   = inst::Bitxor{},
			.for_float = inst::Bitxor{},
		};



		const BinOp shift_l {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::ShiftL{},
			.for_int   = inst::ShiftL{},
			.for_float = inst::ShiftL{},
		};



		const BinOp shift_r {
			.deduce    = type::deduce_bitwise,
			.for_any   = inst::ShiftR{},
			.for_int   = inst::ShiftR{},
			.for_float = inst::ShiftR{},
		};



		inst::Instruction pick_instruction(
			const type::Type & l,
			const type::Type & r,
			const BinOp & op) {
			if(l == r) {
				if(type::is_int(l)) {
					std::cout << "int X int\n";
					return op.for_int;
				}  
				if(type::is_float(l)) { 
					std::cout << "float X float\n";
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
			
			buf << ltn::inst::Ifelse{falsE};
			buf << r.code;
			buf << ltn::inst::CastBool{};
			buf << ltn::inst::Jump{end};

			buf << ltn::inst::Label{falsE};
			buf << ltn::inst::False{};

			buf << ltn::inst::Label{end};
			
			return {
				.code = buf,
				.deduced_type = type::deduce_logic(l.deduced_type,r.deduced_type)
			};
		}



		ExprResult log_or(const ExprResult & l, const ExprResult & r) {
			const auto id = make_jump_id("OR");
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			InstructionBuffer buf;
			
			buf << l.code;
			buf << ltn::inst::Not{};
			buf << ltn::inst::Ifelse{truE};
			buf << r.code;
			buf << ltn::inst::CastBool{};
			buf << ltn::inst::Jump{end};

			buf << ltn::inst::Label{truE};
			buf << ltn::inst::True{};

			buf << ltn::inst::Label{end};
			
			return { 
				.code = buf,
				.deduced_type = type::deduce_logic(l.deduced_type, r.deduced_type)
			};
		}



		ExprResult elvis(const ExprResult & l, const ExprResult & r) {
			const auto jumpmark = make_jump_id("ELVIS");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			
			buf << l.code;
			buf << ltn::inst::Duplicate{};
			buf << ltn::inst::Ifelse{jumpmark_else};
			buf << ltn::inst::Jump{jumpmark_end};

			buf << ltn::inst::Label{jumpmark_else};
			buf << ltn::inst::Scrap{};
			buf << r.code;
			
			buf << ltn::inst::Label{jumpmark_end};
			
			return {
				.code = buf,
				.deduced_type = type::deduce_elvis(l.deduced_type, r.deduced_type)
			};
		}



		ExprResult nullco(const ExprResult & l, const ExprResult & r) {
			const auto jumpmark = make_jump_id("NULLCO");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			InstructionBuffer buf;
			buf << l.code;
			buf << ltn::inst::Duplicate{};
			buf << ltn::inst::Null{};
			buf << ltn::inst::Ueql{};
			buf << ltn::inst::Ifelse{jumpmark_else};
			buf << ltn::inst::Jump{jumpmark_end};

			buf << ltn::inst::Label{jumpmark_else};
			buf << ltn::inst::Scrap{};
			buf << r.code;
			
			buf << ltn::inst::Label{jumpmark_end};
			return {
				.code = buf,
				.deduced_type = type::deduce_nullco(l.deduced_type, r.deduced_type)
			};
		}
	}



	// compiles a binary operation
	ExprResult compile_binary(const ast::Binary & binary, CompilerInfo & info, Scope & scope) {
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