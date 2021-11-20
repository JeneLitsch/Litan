#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		ExprCode integer(const ast::Integer & expr) {
			return ExprCode{inst::newi(expr.value), false, true};
		}

		ExprCode floating(const ast::Float & expr) {
			return ExprCode{ inst::newf(expr.value), false, true };
		}

		ExprCode boolean(const ast::Bool & expr) {
			const auto inst = (expr.value ? inst::truE : inst::falsE);
			return ExprCode{ std::string(inst), false, true};
		}

		ExprCode newvalue(const ast::New & expr) {
			if(expr.type == ast::New::Type::ARRAY) {
				return ExprCode{ std::string(inst::newarr), false, true};
			}
			throw CompilerError{"Unknown new type", expr.debugInfo.line};
		}

		ExprCode readVar(const ast::Var & expr, Scope & scope) {
			const auto ref = compile::varRef(expr, scope);
			std::stringstream ss;
			ss << ref.code;
			ss << inst::read;
			return ExprCode{ ss.str(), false, true};
		}
	}

	ExprCode primary(const ast::Primary & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Integer>(expr)) return integer(*expr_);
		if(auto expr_ = as<ast::Float>(expr)) 	return floating(*expr_);
		if(auto expr_ = as<ast::Bool>(expr)) 	return boolean(*expr_);
		if(auto expr_ = as<ast::New>(expr)) 	return newvalue(*expr_);
		if(auto expr_ = as<ast::Var>(expr)) 	return readVar(*expr_, scope);
		throw CompilerError{"Unknown primary expression", expr.debugInfo.line};
	}
}