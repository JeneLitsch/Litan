#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		ExprCode writeVar(const ast::Var & expr, Scope & scope) {
			const auto addr = compile::addr(expr, scope);
			std::stringstream ss;
			ss << addr.code;
			ss << inst::write;
			return ExprCode{ss.str(), true, false};
		}
	}

	ExprCode addr(const ast::Var & expr, Scope & scope) {
		const auto addr = scope.resolve(expr.name, expr.debugInfo.line);
		std::stringstream ss;
		ss << inst::addr(addr);
		return ExprCode{ss.str(), true, false};
	}

	ExprCode assignable(const ast::Assignable & expr, CompilerInfo &, Scope & scope) {
		if(auto expr_ = as<ast::Var>(expr)) {
			return writeVar(*expr_, scope);
		}
		throw std::runtime_error{"Unknow assingable type"};
	}
}