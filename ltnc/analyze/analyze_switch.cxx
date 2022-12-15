#include "analyze.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	auto analyze_cases(
		auto && body_fx,
		const auto & sw1tch,
		CompilerInfo & info,
		Scope & scope) {
		
		using BodyExpr = decltype(body_fx(sw1tch, info, scope));

		InvalidFunctionTable fx_table {"case"};
		InvalidFunctionTemplateTable fx_template_table {"case"};
		InvalidGlobalTable global_table {"case"};
		CompilerInfo case_info {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue		   = info.fx_queue,
			.definition_table = info.definition_table, 
			.member_table = info.member_table, 
			.global_table = global_table,
			.reporter = info.reporter
		};

		MajorScope case_scope {
			scope.get_namespace(),
			true
		};

		std::vector<std::pair<sst::expr_ptr, BodyExpr>> cases;

		for(const auto & [expr, body] : sw1tch.cases) {
			cases.push_back({
				analyze_expression(*expr, case_info, case_scope),
				body_fx(*body, info, scope)
			});
		}

		return cases;
	}



	sst::stmt_ptr analyze_stmt(
		const ast::StmtSwitch & sw1tch,
		CompilerInfo & info,
		Scope & scope) {
		
		auto condition = analyze_expression(*sw1tch.condition, info, scope);
		auto cases = analyze_cases(analyze_statement, sw1tch, info, scope);
		auto def4ault = analyze_statement(*sw1tch.d3fault, info, scope);


		auto sst_sw1tch = std::make_unique<sst::StmtSwitch>(0, false);
		sst_sw1tch->cases = std::move(cases);
		sst_sw1tch->condition = std::move(condition);
		sst_sw1tch->d3fault = std::move(def4ault);
		return sst_sw1tch;
	}



	sst::expr_ptr analyze_expr(
		const ast::ExprSwitch & sw1tch,
		CompilerInfo & info,
		Scope & scope) {
		
		auto condition = analyze_expression(*sw1tch.condition, info, scope);
		auto cases = analyze_cases(analyze_expression, sw1tch, info, scope);
		auto def4ault = analyze_expression(*sw1tch.d3fault, info, scope);

		type::Type deduced_type = def4ault->type;
		for(const auto & [expr, body] : cases) {
			deduced_type = type::deduce_choose(deduced_type, body->type);
		}

		auto choose = std::make_unique<sst::ExprSwitch>(deduced_type);
		choose->cases = std::move(cases);
		choose->condition = std::move(condition);
		choose->d3fault = std::move(def4ault);
		return choose;
	}
}