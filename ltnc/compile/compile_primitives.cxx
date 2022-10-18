#include "compile.hxx"
#include <string_view>
namespace ltn::c {
	// compiles int literal
	ExprCode compile_integer(const ast::Integer & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newi{expr.value};
		return {
			.code = buf,
			.deduced_type = type::Int{}
		};
	}



	// compiles float literal
	ExprCode compile_floating(const ast::Float & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newf{expr.value};
		return { 
			.code = buf,
			.deduced_type = type::Float{},
		};
	}



	// compiles bool literal
	ExprCode compile_boolean(const ast::Bool & expr) {
		InstructionBuffer buf;
		if(expr.value) {
			buf << ltn::inst::True{};
		}
		else {
			buf << ltn::inst::False{};
		}
		return ExprCode{ 
			.code = buf,
			.deduced_type = type::Bool{}
		};
	}



	// compiles null literal
	ExprCode compile_null(const ast::Null &) {
		InstructionBuffer buf;
		buf << ltn::inst::Null{};
		return ExprCode{ 
			.code = buf,
			.deduced_type = type::Null{}
		};
	}


	// compiles bool literal
	ExprCode compile_character(const ast::Char & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newc{static_cast<std::uint8_t>(expr.value)};
		return ExprCode{
			.code = buf,
			.deduced_type = type::Char{}
		};
	}



	// compiles string literal
	ExprCode compile_string(const ast::String & expr) {
		InstructionBuffer buf;
		std::vector<std::uint8_t> bytes {std::begin(expr.value), std::end(expr.value)};
		buf << ltn::inst::Newstr{ bytes };
		return ExprCode{
			.code = buf,
			.deduced_type = type::String{}
		};
	}
}