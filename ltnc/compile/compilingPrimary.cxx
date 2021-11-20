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

		ExprCode var(const ast::Var & expr, Scope & scope, bool write) {
			const auto addr = scope.resolve(expr.name, expr.debugInfo.line);
			std::stringstream ss;
			ss << inst::newref(addr);
			if(!write) {
				ss << inst::read;
			}
			return ExprCode{ss.str(), true, false};
		}

	}

	ExprCode primary(const ast::Primary & expr, CompilerInfo &, Scope & scope, bool write) {
		if(auto expr_ = as<ast::Integer>(expr)) return integer(*expr_);
		if(auto expr_ = as<ast::Float>(expr)) 	return floating(*expr_);
		if(auto expr_ = as<ast::Bool>(expr)) 	return boolean(*expr_);
		if(auto expr_ = as<ast::New>(expr)) 	return newvalue(*expr_);
		if(auto expr_ = as<ast::Var>(expr)) 	return var(*expr_, scope, write);
		throw CompilerError{"Unknown primary expression", expr.debugInfo.line};
	}
}