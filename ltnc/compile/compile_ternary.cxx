#include "compile.hxx"

namespace ltn::c::compile {
	namespace {
		std::string ternary_id() {
			return make_jump_id("TERNARY");
		}

		std::string jump_else(const std::string & id) {
			return id + "_ELSE";
		}

		std::string jump_end(const std::string & id) {
			return id + "_END";
		}
	}


	ExprCode ternary(const ast::Ternary & expr, CompilerInfo & info, Scope & scope) {
		const auto code_condition = expression(*expr.condition, info, scope).code;
		const auto code_if        = expression(*expr.if_branch, info, scope).code;
		const auto code_else      = expression(*expr.else_branch, info, scope).code;
		
		std::ostringstream ss;
		
		const auto id = ternary_id();
		const auto to_else = jump_else(id); 
		const auto to_end = jump_end(id);
		
		ss << code_condition;
		ss << inst::ifelse(to_else);

		ss << code_if;
		ss << inst::jump(to_end);

		ss << inst::jumpmark(to_else);
		ss << code_else;

		ss << inst::jumpmark(to_end);

		return ExprCode{ss.str()};
	}
}