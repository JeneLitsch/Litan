#include "compile.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	auto compile_cases(auto && body_fx, const auto & sw1tch) {
		std::vector<std::pair<InstructionBuffer, InstructionBuffer>> cases;

		for(const auto & [expr, body] : sw1tch.cases) {
			cases.push_back({compile_expression(*expr), body_fx(*body)});
		}

		return cases;
	}



	auto any_switch(
		const auto & condition,
		const auto & cases,
		const auto & def4ult) {
		
		InstructionBuffer buf;

		const auto id = make_jump_id("SWITCH");
		const auto jump_end = id + "_END";

		buf << condition;
		
		std::size_t i = 0;

		for(const auto & [expr, body] : cases) {
			buf << inst::label(id + "_CASE_" + std::to_string(i+0));
			buf << inst::duplicate();
			buf << expr;
			buf << inst::eql();
			buf << inst::ifelse(id + "_CASE_" + std::to_string(i+1));
			buf << inst::scrap();
			buf << body;
			buf << inst::jump(jump_end);
			++i;
		}

		buf << inst::label(id + "_CASE_" + std::to_string(i+0));
		buf << inst::scrap();
		buf << def4ult;
		buf << inst::label(jump_end);

		return buf;
	}



	InstructionBuffer compile_stmt(const sst::Switch & sw1tch) {
		
		const auto condition = compile_expression(*sw1tch.condition);
		const auto cases = compile_cases(compile_statement, sw1tch);
		const auto def4ault = compile_statement(*sw1tch.d3fault);
		return any_switch(condition, cases, def4ault); 
	}



	InstructionBuffer compile_expr(const sst::Choose & sw1tch) {
		
		const auto condition = compile_expression(*sw1tch.condition);
		const auto cases = compile_cases(compile_expression, sw1tch);
		const auto def4ault = compile_expression(*sw1tch.d3fault);
		return any_switch(condition, cases, def4ault);
	}
}