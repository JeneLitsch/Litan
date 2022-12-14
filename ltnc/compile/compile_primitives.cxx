#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	InstructionBuffer compile_expr(const sst::Integer & expr) {
		InstructionBuffer buf;
		buf << inst::newi(expr.value);
		return buf;
	}



	// compiles float literal
	InstructionBuffer compile_expr(const sst::Float & expr) {
		InstructionBuffer buf;
		buf << inst::newf(expr.value);
		return buf;

	}



	// compiles bool literal
	InstructionBuffer compile_expr(const sst::Bool & expr) {
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
	InstructionBuffer compile_expr(const sst::Null &) {
		InstructionBuffer buf;
		buf << inst::null();
		return buf;
	}


	// compiles bool literal
	InstructionBuffer compile_expr(const sst::Char & expr) {
		InstructionBuffer buf;
		buf << inst::newc(static_cast<std::uint8_t>(expr.value));
		return buf;
	}



	// compiles string literal
	InstructionBuffer compile_expr(const sst::String & expr) {
		InstructionBuffer buf;
		buf << inst::newstr(expr.value);
		return buf;
	}
}