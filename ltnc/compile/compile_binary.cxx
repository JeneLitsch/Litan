#include "compile.hxx"

namespace ltn::c {
	namespace {
		using OP = ltn::c::ast::Binary::Type;
		
		
		
		ExprCode bin(
			const auto & l,
			const auto & r,
			const auto ... inst) {
			InstructionBuffer buf;
			buf << l.code;
			buf << r.code;
			(buf << ... << inst);
			return { buf };
		}



		ExprCode log_and(const ExprCode & l, const ExprCode & r) {
			const auto id = make_jump_id("AND");
			const auto end = id + "_END";
			const auto falsE = id + "FALSE";
			InstructionBuffer buf;
			buf << l.code;
			
			buf << ltn::inst::Ifelse{falsE};
			buf << r.code;
			buf << ltn::inst::Jump{end};

			buf << ltn::inst::Label{falsE};
			buf << ltn::inst::False{};

			buf << ltn::inst::Label{end};
			
			return { buf };
		}



		ExprCode log_or(const ExprCode & l, const ExprCode & r) {
			const auto id = make_jump_id("OR");
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			InstructionBuffer buf;
			
			buf << l.code;
			buf << ltn::inst::Not{};
			buf << ltn::inst::Ifelse{truE};
			buf << r.code;
			buf << ltn::inst::Jump{end};

			buf << ltn::inst::Label{truE};
			buf << ltn::inst::True{};

			buf << ltn::inst::Label{end};
			
			return { buf };
		}



		ExprCode elvis(const ExprCode & l, const ExprCode & r) {
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
			
			return { buf };
		}


		ExprCode nullco(const ExprCode & l, const ExprCode & r) {
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
			return { buf };
		}


		ExprCode chain(const auto & l, const auto & r) {
			InstructionBuffer buf;
			buf << l.code;
			buf << r.code;
			buf << ltn::inst::Call{"_op_chain"};
			return ExprCode{ buf };
		}

	}



	// compiles a binary operation
	ExprCode compile_binary(const ast::Binary & binary, CompilerInfo & info, Scope & scope) {
		const auto l = compile_expression(*binary.l, info, scope);
		const auto r = compile_expression(*binary.r, info, scope);
		switch (binary.type) {
			case OP::ADD:          return bin(l, r, ltn::inst::Add{});
			case OP::SUB:          return bin(l, r, ltn::inst::Sub{});
			case OP::MLT:          return bin(l, r, ltn::inst::Mlt{});
			case OP::DIV:          return bin(l, r, ltn::inst::Div{});
			case OP::MOD:          return bin(l, r, ltn::inst::Mod{});
			case OP::POW:          return bin(l, r, ltn::inst::Pow{});
			case OP::SMALLER:      return bin(l, r, ltn::inst::Sml{});
			case OP::BIGGER:       return bin(l, r, ltn::inst::Bgr{});
			case OP::SMALLEREQUAL: return bin(l, r, ltn::inst::Smleql{});
			case OP::BIGGEREQUAL:  return bin(l, r, ltn::inst::Bgreql{});
			case OP::EQUAL:        return bin(l, r, ltn::inst::Eql{});
			case OP::UNEQUEL:      return bin(l, r, ltn::inst::Ueql{});
			case OP::SPACE_SHIP:   return bin(l, r, ltn::inst::Comp{});
			case OP::SHIFT_L:      return bin(l, r, ltn::inst::ShiftL{});
			case OP::SHIFT_R:      return bin(l, r, ltn::inst::ShiftR{});
			case OP::BIT_AND:      return bin(l, r, ltn::inst::Bitand{});
			case OP::BIT_OR:       return bin(l, r, ltn::inst::Bitor{});
			case OP::BIT_XOR:      return bin(l, r, ltn::inst::Bitxor{});
			case OP::AND:          return log_and(l, r);
			case OP::OR:           return log_or(l, r);
			case OP::ELVIS:        return elvis(l, r);
			case OP::NULLCO:       return nullco(l, r);
		}
		throw CompilerError{"Invalid binary operation", {}};
	}
	
}