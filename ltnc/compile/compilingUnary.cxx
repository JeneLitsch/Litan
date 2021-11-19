#include "compiling.hxx"

namespace ltn::c::compile {
	CompilerError cannotNegate(
		const type::Type & type,
		const lex::DebugInfo & debug) {
		std::stringstream ss;
		ss << "Cannot negate " << type;
		return { ss.str(), debug.line };
	} 

	ExprCode negate(const ast::Expression & expr, CompilerInfo & info) {
		const auto code = expression(expr, info);
		std::stringstream ss;
		ss << code.code;
		if(type::isInt(code.type)) {
			ss << inst::negi;
		} else 
		if(type::isFloat(code.type)) {
			ss << inst::negf;
		}
		else {
			throw cannotNegate(code.type, expr.debugInfo);
		}
		
		return ExprCode{ss.str(), false, code.constant, code.type };
	}

	ExprCode notigate (const ast::Expression & expr, CompilerInfo & info) {
		const auto code = expression(expr, info);
		std::stringstream ss;
		ss << code.code;
		if(type::isBool(code.type)) {
			ss << inst::negi;
		} 
		else {
			throw cannotNegate(code.type, expr.debugInfo);
		}
		
		return ExprCode{ss.str(), false, code.constant, code.type };
	}
	
	ExprCode unary(const ast::Unary & expr, CompilerInfo & info) {
		if(expr.type == ast::Unary::Type::NEG) {
			return negate(*expr.expression, info);
		}
		if(expr.type == ast::Unary::Type::NOT) {
			return notigate(*expr.expression, info);
		}
		throw CompilerError{"Unknown unary expression", expr.debugInfo.line};
	}
}