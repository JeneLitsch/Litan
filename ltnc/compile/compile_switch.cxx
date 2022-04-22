#include "compile.hxx"
namespace ltn::c::compile {
	// compiles -> return...;
	StmtCode stmt_switch(const ast::StmtSwitch & sw1tch, CompilerInfo & info, Scope & scope) {
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
			oss << compile::statement(*body, info, scope).code;
			oss << inst::jump(jump_end);
			++i;
		}

		oss << inst::jumpmark(id + "_CASE_" + std::to_string(i+0));
		oss << inst::scrap;
		oss << inst::jumpmark(jump_end);

		return StmtCode{oss.str(), 0, false};
	}
}