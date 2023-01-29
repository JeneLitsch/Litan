#include "analyze.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {



	auto analyze_cases(
		auto body_fx,
		const auto & sw1tch,
		Context & context,
		Scope & scope) {
		
		using BodyExpr = decltype(body_fx(sw1tch, context, scope));

		InvalidFunctionTable fx_table {"case"};
		InvalidFunctionTemplateTable fx_template_table {"case"};
		InvalidGlobalTable global_table {"case"};
		Context case_context {
			.fx_table = fx_table,
			.fx_template_table = fx_template_table,
			.fx_queue		   = context.fx_queue,
			.definition_table = context.definition_table, 
			.member_table = context.member_table, 
			.global_table = global_table,
			.reporter = context.reporter
		};

		MajorScope case_scope {
			scope.get_namespace(),
			true
		};

		return stx::fx::mapped(stx::fx::paired(
			[&] (auto & c4se) { return analyze_expression(*c4se, case_context, case_scope); },
			[&] (auto & body) { return body_fx(*body, context, scope); }
		)) (sw1tch.cases);
	}



	sst::stmt_ptr analyze_stmt(
		const ast::StmtSwitch & sw1tch,
		Context & context,
		Scope & scope) {
		
		auto condition = analyze_expression(*sw1tch.condition, context, scope);
		auto cases = analyze_cases(analyze_statement, sw1tch, context, scope);
		auto def4ault = analyze_statement(*sw1tch.d3fault, context, scope);


		auto sst_sw1tch = std::make_unique<sst::StmtSwitch>();
		sst_sw1tch->cases = std::move(cases);
		sst_sw1tch->condition = std::move(condition);
		sst_sw1tch->d3fault = std::move(def4ault);
		return sst_sw1tch;
	}



	sst::expr_ptr analyze_expr(
		const ast::ExprSwitch & sw1tch,
		Context & context,
		Scope & scope) {

		auto condition = analyze_expression(*sw1tch.condition, context, scope);
		auto cases = analyze_cases(analyze_expression, sw1tch, context, scope);
		auto def4ault = analyze_expression(*sw1tch.d3fault, context, scope);

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