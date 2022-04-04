#include "compile.hxx"

namespace ltn::c::compile {
	namespace {
		using OP = ltn::c::ast::Binary::Type;
		
		
		
		ExprCode bin(
			const auto & l,
			const auto & r,
			const std::string_view inst) {
			std::ostringstream ss;
			ss << l.code;
			ss << r.code;
			ss << inst;
			return { ss.str() };
		}



		ExprCode log_and(const auto & l, const auto & r, CompilerInfo & info) {
			const auto id = make_jump_id("AND");
			const auto end = id + "_END";
			const auto falsE = id + "_FALSE";
			std::stringstream ss;
			ss << l.code;
			
			ss << inst::ifelse(falsE);
			ss << r.code;
			ss << inst::jump(end);

			ss << inst::jumpmark(falsE);
			ss << inst::falsE;

			ss << inst::jumpmark(end);
			
			return { ss.str() };
		}



		ExprCode log_or(const auto & l, const auto & r, CompilerInfo & info) {
			const auto id = make_jump_id("OR");
			const auto end = id + "_END";
			const auto truE = id + "_TRUE";
			std::stringstream ss;
			
			ss << l.code;
			ss << inst::n0t;
			ss << inst::ifelse(truE);
			ss << r.code;
			ss << inst::jump(end);

			ss << inst::jumpmark(truE);
			ss << inst::truE;

			ss << inst::jumpmark(end);
			
			
			return { ss.str() };
		}



		ExprCode elvis(const auto & l, const auto & r, CompilerInfo & info) {
			const auto jumpmark = make_jump_id("ELVIS");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			std::ostringstream ss;
			ss << l.code;
			ss << inst::duplicate;
			ss << inst::ifelse(jumpmark_else);
			ss << inst::jump(jumpmark_end);

			ss << inst::jumpmark(jumpmark_else);
			ss << inst::scrap;
			ss << r.code;
			
			ss << inst::jumpmark(jumpmark_end);
			return {ss.str()};
		}


		ExprCode nullco(const auto & l, const auto & r, CompilerInfo & info) {
			const auto jumpmark = make_jump_id("NULLCO");
			const auto jumpmark_else = jumpmark + "_ELSE"; 
			const auto jumpmark_end = jumpmark + "_END"; 
			std::ostringstream ss;
			ss << l.code;
			ss << inst::duplicate;
			ss << inst::null;
			ss << inst::ueql;
			ss << inst::ifelse(jumpmark_else);
			ss << inst::jump(jumpmark_end);

			ss << inst::jumpmark(jumpmark_else);
			ss << inst::scrap;
			ss << r.code;
			
			ss << inst::jumpmark(jumpmark_end);
			return {ss.str()};
		}

	}

	// compiles a binary operation
	ExprCode binary(const ast::Binary & binary, CompilerInfo & info, Scope & scope) {
		const auto l = compile::expression(*binary.l, info, scope);
		const auto r = compile::expression(*binary.r, info, scope);
		switch (binary.type) {
			case OP::ADD:          return bin(l, r, inst::add);
			case OP::SUB:          return bin(l, r, inst::sub);
			case OP::MLT:          return bin(l, r, inst::mlt);
			case OP::DIV:          return bin(l, r, inst::div);
			case OP::MOD:          return bin(l, r, inst::mod);
			case OP::SMALLER:      return bin(l, r, inst::sml);
			case OP::BIGGER:       return bin(l, r, inst::bgr);
			case OP::SMALLEREQUAL: return bin(l, r, inst::smleql);
			case OP::BIGGEREQUAL:  return bin(l, r, inst::bgreql);
			case OP::EQUAL:        return bin(l, r, inst::eql);
			case OP::UNEQUEL:      return bin(l, r, inst::ueql);
			case OP::SPACE_SHIP:   return bin(l, r, inst::comp);
			case OP::APPROX:       return bin(l, r, inst::approx);
			case OP::NOTPROX:      return bin(l, r, inst::notprox);
			case OP::SHIFT_L:      return bin(l, r, inst::shift_l);
			case OP::SHIFT_R:      return bin(l, r, inst::shift_r);
			case OP::AND:          return log_and(l, r, info);
			case OP::OR:           return log_or(l, r, info);
			case OP::ELVIS:        return elvis(l, r, info);
			case OP::NULLCO:       return nullco(l, r, info);
		}
		throw CompilerError{"Invalid binary operation", {}};
	}
	
}