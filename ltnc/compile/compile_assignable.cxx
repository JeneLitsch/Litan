#include "compile.hxx"

namespace ltn::c::compile {
	namespace {
		CompilerError not_mutable(const SourceLocation & location) {
			return CompilerError{
				"Cannot modify non-mutable variable",
				location};
		}

		// write to an local variable
		ExprCode write_variable(const ast::Var & expr, Scope & scope) {
			const auto var = scope.resolve(expr.name, expr.location);
			if(is_mutable(var)) {
				std::stringstream ss;
				ss << inst::write_x(var.address);
				return ExprCode{ss.str() };
			}
			else throw not_mutable(expr.location);
		}

		// write to an array at index [i]
		ExprCode write_index(const ast::Index & expr, CompilerInfo & info, Scope & scope) {
			const auto arr = expression(*expr.expression, info, scope);
			const auto idx = expression(*expr.index, info, scope);
			std::stringstream ss;
			ss << arr.code;
			ss << idx.code;
			ss << inst::at_write;
			return ExprCode{ss.str() };
		}

		ExprCode write_member(const ast::Member & expr, CompilerInfo & info, Scope & scope) {
			std::stringstream ss;
			ss << expression(*expr.expr, info, scope).code;
			const auto id = info.member_table.get_id(expr.name);
			ss << inst::member_write(id);

			return ExprCode{ss.str() };
		}
	}

	// compile assignable variable
	ExprCode assignable(const ast::Assignable & expr, CompilerInfo & info, Scope & scope) {
		if(auto expr_ = as<ast::Var>(expr)) {
			return write_variable(*expr_, scope);
		}
		if(auto expr_ = as<ast::Index>(expr)) {
			return write_index(*expr_, info, scope);
		}
		if(auto expr_ = as<ast::Member>(expr)) {
			return write_member(*expr_, info, scope);
		}
		throw std::runtime_error{"Unknow assingable type"};
	}
}