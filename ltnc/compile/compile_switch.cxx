#include "compile.hxx"
namespace ltn::c::compile {
	template<auto body_fx>
	auto any_switch(const auto & sw1tch, CompilerInfo & info, Scope & scope) {
		std::ostringstream oss;

		const auto id = make_jump_id("SWITCH");
		const auto jump_end = id + "_END";

		oss << compile::expression(*sw1tch.condition, info, scope).code;
		
		std::size_t i = 0;

		for(const auto & [expr, body] : sw1tch.cases) {
			
			oss << inst::jumpmark(id + "_CASE_" + std::to_string(i+0));
			oss << inst::duplicate;
			oss << compile::expression(*expr, info, scope).code;
			oss << inst::eql;
			oss << inst::ifelse(id + "_CASE_" + std::to_string(i+1));
			oss << inst::scrap;
			oss << body_fx(*body, info, scope).code;
			oss << inst::jump(jump_end);
			++i;
		}

		oss << inst::jumpmark(id + "_CASE_" + std::to_string(i+0));
		oss << inst::scrap;
		oss << body_fx(*sw1tch.d3fault, info, scope).code;
		oss << inst::jumpmark(jump_end);

		return oss.str();
	}



	// compiles -> return...;
	StmtCode stmt_switch(const ast::StmtSwitch & sw1tch, CompilerInfo & info, Scope & scope) {
		return StmtCode {
			any_switch<compile::statement>(sw1tch, info, scope), 0, false};
	}



	// compiles -> return...;
	ExprCode expr_switch(const ast::ExprSwitch & sw1tch, CompilerInfo & info, Scope & scope) {
		return ExprCode {
			any_switch<compile::expression>(sw1tch, info, scope)};
	}
}