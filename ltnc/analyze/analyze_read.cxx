#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::Var & expr, Scope & scope) {
		if(expr.namespaze.empty()) {
			if(auto local = scope.resolve_variable(expr.name, location(expr))) {
				return std::make_unique<sst::Var>(local->address, local->type);
			}
		}
		
		if(auto def = scope.resolve_definiton(expr.name, expr.namespaze)) {
			return std::make_unique<sst::GlobalVar>(def->type, def->id);
		}

		if(auto glob = scope.resolve_global(expr.name,	expr.namespaze)) {
			return std::make_unique<sst::GlobalVar>(glob->type, glob->id);
		}
		
		throw undefined_variable(expr);
	}

	
	
	sst::expr_ptr analyze_expr(const ast::Member & access, Scope & scope) {
		const auto id = scope.resolve_member_id(access.name);
		auto expr = analyze_expression(*access.expr, scope);
		return std::make_unique<sst::Member>(type::Any{}, std::move(expr), id);
	}
}