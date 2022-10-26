#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	ExprResult compile_integer(const ast::Integer & expr) {
		InstructionBuffer buf;
		buf << inst::newi(expr.value);
		return {
			.code = buf,
			.deduced_type = type::Int{}
		};
	}



	// compiles float literal
	ExprResult compile_floating(const ast::Float & expr) {
		InstructionBuffer buf;
		buf << inst::newf(expr.value);
		return { 
			.code = buf,
			.deduced_type = type::Float{},
		};
	}



	// compiles bool literal
	ExprResult compile_boolean(const ast::Bool & expr) {
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
	ExprResult compile_null(const ast::Null &) {
		InstructionBuffer buf;
		buf << inst::null();
		return ExprResult{ 
			.code = buf,
			.deduced_type = type::Null{}
		};
	}


	// compiles bool literal
	ExprResult compile_character(const ast::Char & expr) {
		InstructionBuffer buf;
		buf << inst::newc(static_cast<std::uint8_t>(expr.value));
		return ExprResult{
			.code = buf,
			.deduced_type = type::Char{}
		};
	}



	// compiles string literal
	ExprResult compile_string(const ast::String & expr) {
		InstructionBuffer buf;
		std::vector<std::uint8_t> bytes {std::begin(expr.value), std::end(expr.value)};
		buf << inst::newstr(bytes);
		return ExprResult{
			.code = buf,
			.deduced_type = type::String{}
		};
	}
}