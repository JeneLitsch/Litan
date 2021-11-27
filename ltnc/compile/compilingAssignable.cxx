#include "compiling.hxx"

namespace ltn::c::compile {
	namespace {
		// write to an local variable
		ExprCode writeVar(const ast::Var & expr, Scope & scope) {
			const auto addr = scope.resolve(expr.name, expr.debugInfo.line);
			std::stringstream ss;

			switch (addr) {
			// Shortcut instructions
			case 0: ss << inst::write_0; break;
			case 1: ss << inst::write_1; break;
			case 2: ss << inst::write_2; break;
			case 3: ss << inst::write_3; break;
			// Standard instructions
			default: ss << inst::addr(addr) << inst::write; break;
			}
			return ExprCode{ss.str(), false, false};
		}

		// write to an array at index [i]
		ExprCode writeIndex(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto arr = expression(*expr.expression, info, scope);
			const auto idx = expression(*expr.index, info, scope);
			std::stringstream ss;
			ss << arr.code;
			ss << idx.code;
			ss << inst::at_write;
			return ExprCode{ss.str(), false, false};
		}
	}

	// compile assignable variable
	ExprCode assignable(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Var>(expr)) {
			return writeVar(*expr_, scope);
		}
		if(auto expr_ = as<ast::Index>(expr)) {
			return writeIndex(*expr_, info, scope);
		}
		throw std::runtime_error{"Unknow assingable type"};
	}
}