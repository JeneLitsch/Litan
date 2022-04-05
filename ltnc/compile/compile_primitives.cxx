#include "compile.hxx"
#include <string_view>
namespace ltn::c::compile {
	// compiles int literal
	ExprCode integer(const ast::Integer & expr) {
		return ExprCode{inst::newi(expr.value) };
	}



	// compiles float literal
	ExprCode floating(const ast::Float & expr) {
		return ExprCode{ inst::newf(expr.value) };
	}



	// compiles bool literal
	ExprCode boolean(const ast::Bool & expr) {
		const auto inst = (expr.value ? inst::truE : inst::falsE);
		return ExprCode{ std::string(inst) };
	}



	// compiles null literal
	ExprCode null(const ast::Null &) {
		return ExprCode{ std::string(inst::null) };
	}


	// compiles bool literal
	ExprCode character(const ast::Char & expr) {
		return ExprCode{ inst::newc(expr.value) };
	}



	// compiles string literal
	ExprCode string(const ast::String & expr) {
		return ExprCode{ inst::newstr(expr.value) };
	}
}