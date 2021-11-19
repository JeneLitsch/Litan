#include "compiling.hxx"

namespace ltn::c::compile {

	ExprCode literal(const std::string & code, const std::string_view & type) {
		return ExprCode{code, false, true, type::Type(type)};
	}

	ExprCode integer(const ast::Integer & expr) {
		return literal(inst::newi(expr.value), type::TInt);
	}

	ExprCode floating(const ast::Float & expr) {
		return literal(inst::newf(expr.value), type::TFloat);
	}

	ExprCode boolean(const ast::Bool & expr) {
		const auto inst = (expr.value ? inst::truE : inst::falsE);
		return literal(std::string(inst), type::TBool);
	}
	
	ExprCode primary(const ast::Primary & expr, CompilerInfo & info) {
		if(auto expr_ = as<ast::Integer>(expr)) return integer(*expr_);
		if(auto expr_ = as<ast::Float>(expr)) 	return floating(*expr_);
		if(auto expr_ = as<ast::Bool>(expr)) 	return boolean(*expr_);
		throw CompilerError{"Unknown primary expression", expr.debugInfo.line};
	}
}