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

		ExprCode string(const ast::String & expr) {
			std::stringstream ss;
			ss << inst::alloc_string << std::hex;
			for(char chr : expr.value) {
				ss << inst::ch4r(chr);
			}
			return ExprCode{ ss.str(), false, true};
		}

		ExprCode newvalue(const ast::New & expr) {
			if(expr.type == ast::New::Type::ARRAY) {
				return ExprCode{ std::string(inst::newarr), false, true};
			}
			throw CompilerError{"Unknown new type", expr.debugInfo.line};
		}

		ExprCode readVar(const ast::Var & expr, Scope & scope) {
			const auto addr = compile::addr(expr, scope);
			std::stringstream ss;
			ss << addr.code;
			ss << inst::read;
			return ExprCode{ ss.str(), false, true};
		}

		ExprCode callFx(const ast::Call & call, CompilerInfo & info, Scope & scope) {
			const auto fx = info.fxTable.find(call.name, call.parameters.size());
			if(fx) {
				std::stringstream ss;
				for(const auto & param : call.parameters) {
					const auto paramCode = compile::expression(*param, info, scope);
					ss << paramCode.code;
				}
				ss << inst::call(fx->id);
				return ExprCode{ ss.str(), false, false };
			}
			throw CompilerError {
				"Function " + call.name + " is not defined",
				call.debugInfo.line };
		}
	}

	ExprCode primary(const ast::Primary & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Integer>(expr)) return integer(*expr_);
		if(auto expr_ = as<ast::Float>(expr)) 	return floating(*expr_);
		if(auto expr_ = as<ast::Bool>(expr)) 	return boolean(*expr_);
		if(auto expr_ = as<ast::String>(expr)) 	return string(*expr_);
		if(auto expr_ = as<ast::New>(expr)) 	return newvalue(*expr_);
		if(auto expr_ = as<ast::Call>(expr)) 	return callFx(*expr_, info, scope);
		if(auto expr_ = as<ast::Var>(expr)) 	return readVar(*expr_, scope);
		throw CompilerError{"Unknown primary expression", expr.debugInfo.line};
	}
}