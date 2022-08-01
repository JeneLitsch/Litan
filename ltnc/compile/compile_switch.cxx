#include "compile.hxx"
namespace ltn::c {
	template<auto body_fx>
	auto any_switch(const auto & sw1tch, CompilerInfo & info, Scope & scope) {
		InvalidFunctionTable fx_table {"case"};
		InvalidGlobalTable global_table {"case"};
		CompilerInfo case_info {
			.fx_table = fx_table,
			.definition_table = info.definition_table, 
			.member_table = info.member_table, 
			.global_table = global_table,
			.reporter = info.reporter
		};

		MajorScope case_scope { scope.get_namespace(), true };

		InstructionBuffer buf;

		const auto id = make_jump_id("SWITCH");
		const auto jump_end = id + "_END";

		buf << compile_expression(*sw1tch.condition, info, scope).code;
		
		std::size_t i = 0;

		for(const auto & [expr, body] : sw1tch.cases) {

			buf << ltn::inst::Label{id + "_CASE_" + std::to_string(i+0)};
			buf << ltn::inst::Duplicate{};
			buf << compile_expression(*expr, case_info, case_scope).code;
			buf << ltn::inst::Eql{};
			buf << ltn::inst::Ifelse{id + "_CASE_" + std::to_string(i+1)};
			buf << ltn::inst::Scrap{};
			buf << body_fx(*body, info, scope).code;
			buf << ltn::inst::Jump{jump_end};
			++i;
		}

		buf << ltn::inst::Label{id + "_CASE_" + std::to_string(i+0)};
		buf << ltn::inst::Scrap{};
		buf << body_fx(*sw1tch.d3fault, info, scope).code;
		buf << ltn::inst::Label{jump_end};

		return buf;
	}



	StmtCode compile_stmt_switch(const ast::StmtSwitch & sw1tch, CompilerInfo & info, Scope & scope) {
		return StmtCode {
			any_switch<compile_statement>(sw1tch, info, scope), 0, false};
	}



	ExprCode compile_expr_switch(const ast::ExprSwitch & sw1tch, CompilerInfo & info, Scope & scope) {
		return ExprCode { 
			any_switch<compile_expression>(sw1tch, info, scope)};
	}
}