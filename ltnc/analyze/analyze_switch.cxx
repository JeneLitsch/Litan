#include "analyze.hxx"
#include "stdxx/functional.hxx"

#include "ltnc/ast/expr/Choose.hxx"
#include "ltnc/ast/stmt/Switch.hxx"

#include "ltnc/sst/expr/Switch.hxx"
#include "ltnc/sst/stmt/Switch.hxx"

#include "ltnc/scoping/CaseScope.hxx"

namespace ltn::c {
	auto analyze_cases(auto body_fx, const auto & sw1tch, Scope & scope) {

		CaseScope case_scope { &scope };

		return stx::fx::mapped(stx::fx::paired(
			[&] (auto & c4se) { return analyze_expression(*c4se, case_scope); },
			[&] (auto & body) { 
				MinorScope body_scope {&scope};
				return body_fx(*body, body_scope); }
		)) (sw1tch.cases);
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Switch & sw1tch, Scope & scope) {
		
		auto condition = analyze_expression(*sw1tch.condition, scope);
		auto cases = analyze_cases(analyze_statement, sw1tch, scope);
		auto def4ault = analyze_statement(*sw1tch.d3fault, scope);

		auto sst_sw1tch = sst::stmt::sw1tch();
		sst_sw1tch->cases = std::move(cases);
		sst_sw1tch->condition = std::move(condition);
		sst_sw1tch->d3fault = std::move(def4ault);
		return sst_sw1tch;
	}



	sst::expr_ptr analyze_expr(const ast::expr::Choose & sw1tch, Scope & scope) {

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