#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	ExprResult compile_expr(const sst::Integer & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newi(expr.value);
		return {
			.code = buf,
			.deduced_type = type::Int{}
		};
	}



	// compiles float literal
	ExprResult compile_expr(const sst::Float & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newf(expr.value);
		return { 
			.code = buf,
			.deduced_type = type::Float{},
		};
	}



	// compiles bool literal
	ExprResult compile_expr(const sst::Bool & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		if(expr.value) {
			buf << inst::bool_true();
		}
		else {
			buf << inst::bool_false();
		}
		return ExprResult{ 
			.code = buf,
			.deduced_type = type::Bool{}
		};
	}



	// compiles null literal
	ExprResult compile_expr(const sst::Null &, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::null();
		return ExprResult{ 
			.code = buf,
			.deduced_type = type::Null{}
		};
	}


	// compiles bool literal
	ExprResult compile_expr(const sst::Char & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newc(static_cast<std::uint8_t>(expr.value));
		return ExprResult{
			.code = buf,
			.deduced_type = type::Char{}
		};
	}



	// compiles string literal
	ExprResult compile_expr(const sst::String & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newstr(expr.value);
		return ExprResult{
			.code = buf,
			.deduced_type = type::String{}
		};
	}
}