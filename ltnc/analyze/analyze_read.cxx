#include "analyze.hxx"
#include <string_view>
namespace ltn::c {
	namespace {
		bool is_inner_namespace(
			const Namespace & call_ns,
			const Namespace & fx_ns) {
			if(fx_ns.size() > call_ns.size()) return false;
			for(std::size_t i = 0; i < fx_ns.size(); i++) {
				if(call_ns[i] != fx_ns[i]) {
					return false;
				}
			}
			return true;
		}
	}



	void guard_private(
		const ast::Functional & fx,
		const Namespace & call_ns,
		const SourceLocation & loc) {
		if(
			fx.is_private &&
			!is_inner_namespace(call_ns, fx.namespaze)) {
			throw CompilerError {
				"Function is not visible in current scope",
				loc
			};
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::Var & expr,
		Context & context,
		Scope & scope) {

		const auto & name = expr.name;
		const auto & namespaze = scope.get_namespace();
		
		const auto * var = scope.resolve(expr.name, expr.location);
		if(var && expr.namespaze.empty()) {
			return std::make_unique<sst::Var>(var->address, var->type);
		}
		
		const auto * def = context.definition_table.resolve(
			name,
			namespaze,
			expr.namespaze);
		
		if(!def) {
			throw CompilerError {
				"Undefined variable " + expr.namespaze.to_string() + name,
				expr.location
			};
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