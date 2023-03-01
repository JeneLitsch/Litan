#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	sst::expr_ptr analyze_expr(
		const ast::Var & expr,
		Context & context,
		Scope & scope) {
		
		const auto * var = scope.resolve(expr.name, location(expr));
		if(var && expr.namespaze.empty()) {
			return std::make_unique<sst::Var>(var->address, var->type);
		}
		
		const auto * def = context.definition_table.resolve(
			expr.name,
			scope.get_namespace(),
			expr.namespaze
		);
		
		if(!def) {
			throw undefined_variable(expr);
		}
		
		return std::make_unique<sst::GlobalVar>(
			def->type,
			def->id
		);
	}

	
	
	sst::expr_ptr analyze_expr(
		const ast::Member & access,
		Context & context,
		Scope & scope) {

		const auto id = context.member_table.get_id(access.name);
		auto expr = analyze_expression(*access.expr, context, scope);
		return std::make_unique<sst::Member>(type::Any{}, std::move(expr), id);
	}
}