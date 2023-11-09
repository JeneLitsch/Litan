#include "analyze.hxx"
#include "stdxx/functional.hxx"
#include "ltnc/sst/expr/Choose.hxx"
#include "ltnc/sst/stmt/Switch.hxx"

namespace ltn::c {
	auto analyze_cases(auto body_fx, const auto & sw1tch, Scope & scope) {

		InvalidFunctionTable fx_table {"case"};
		InvalidGlobalTable global_table {"case"};
		auto & outer_context = scope.get_context(); 
		Context case_context {
			.fx_table = fx_table,
			.fx_queue = outer_context.fx_queue,
			.definition_table = outer_context.definition_table, 
			.member_table = outer_context.member_table, 
			.global_table = global_table,
			.reporter = outer_context.reporter,
			.custom_resolver   = outer_context.custom_resolver,
		};

		MajorScope case_scope {
			scope.get_namespace(),
			true,
			case_context
		};

		return stx::fx::mapped(stx::fx::paired(
			[&] (auto & c4se) { return analyze_expression(*c4se, case_scope); },
			[&] (auto & body) { return body_fx(*body, scope); }
		)) (sw1tch.cases);
	}



	sst::stmt_ptr analyze_stmt(const ast::Switch & sw1tch, Scope & scope) {
		
		auto condition = analyze_expression(*sw1tch.condition, scope);
		auto cases = analyze_cases(analyze_statement, sw1tch, scope);
		auto def4ault = analyze_statement(*sw1tch.d3fault, scope);

		auto sst_sw1tch = sst::switch_stmt();
		sst_sw1tch->cases = std::move(cases);
		sst_sw1tch->condition = std::move(condition);
		sst_sw1tch->d3fault = std::move(def4ault);
		return sst_sw1tch;
	}



	sst::expr_ptr analyze_expr(const ast::Choose & sw1tch, Scope & scope) {

		auto condition = analyze_expression(*sw1tch.condition, scope);
		auto cases = analyze_cases(analyze_expression, sw1tch, scope);
		auto def4ault = analyze_expression(*sw1tch.d3fault, scope);

		auto choose = sst::expr::sw1tch();
		choose->cases = std::move(cases);
		choose->condition = std::move(condition);
		choose->d3fault = std::move(def4ault);
		return choose;
	}
}