#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	sst::expr_ptr analyze_expr(const ast::Integer & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newi(expr.value);
		return {
			.code = buf,
			.deduced_type = type::Int{}
		};
	}



	// compiles float literal
	sst::expr_ptr analyze_expr(const ast::Float & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newf(expr.value);
		return { 
			.code = buf,
			.deduced_type = type::Float{},
		};
	}



	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Bool & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		if(expr.value) {
			buf << inst::bool_true();
		}
		else {
			buf << inst::bool_false();
		}
		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = type::Bool{}
		};
	}



	// compiles null literal
	sst::expr_ptr analyze_expr(const ast::Null &, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::null();
		return sst::expr_ptr{ 
			.code = buf,
			.deduced_type = type::Null{}
		};
	}


	// compiles bool literal
	sst::expr_ptr analyze_expr(const ast::Char & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newc(static_cast<std::uint8_t>(expr.value));
		return sst::expr_ptr{
			.code = buf,
			.deduced_type = type::Char{}
		};
	}



	// compiles string literal
	sst::expr_ptr analyze_expr(const ast::String & expr, CompilerInfo &, Scope &) {
		InstructionBuffer buf;
		buf << inst::newstr(expr.value);
		return sst::expr_ptr{
			.code = buf,
			.deduced_type = type::String{}
		};
	}
}