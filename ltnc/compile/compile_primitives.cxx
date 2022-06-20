#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles int literal
	ExprCode integer(const ast::Integer & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newi{expr.value};
		return { buf };
	}



	// compiles float literal
	ExprCode floating(const ast::Float & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newf{expr.value};
		return { buf };
	}



	// compiles bool literal
	ExprCode boolean(const ast::Bool & expr) {
		InstructionBuffer buf;
		if(expr.value) {
			buf << ltn::inst::True{};
		}
		else {
			buf << ltn::inst::False{};
		}
		return ExprCode{ buf };
	}



	// compiles null literal
	ExprCode null(const ast::Null &) {
		InstructionBuffer buf;
		buf << ltn::inst::Null{};
		return ExprCode{ buf };
	}


	// compiles bool literal
	ExprCode character(const ast::Char & expr) {
		InstructionBuffer buf;
		buf << ltn::inst::Newc{static_cast<std::uint8_t>(expr.value)};
		return ExprCode{ buf };
	}



	// compiles string literal
	ExprCode string(const ast::String & expr) {
		InstructionBuffer buf;
		std::vector<std::uint8_t> bytes {std::begin(expr.value), std::end(expr.value)};
		buf << ltn::inst::Newstr{ bytes.size(), bytes };
		return ExprCode{ buf };
	}
}