#include "analyze.hxx"
#include <string_view>

#include "litan_compiler/ast/expr/Member.hxx"
#include "litan_compiler/ast/expr/Var.hxx"

#include "litan_compiler/sst/expr/Member.hxx"
#include "litan_compiler/sst/expr/Var.hxx"
#include "litan_compiler/sst/expr/GlobalVar.hxx"


namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Var & expr, Scope & scope) {
		if(expr.namespaze.empty()) {
			if(auto local = scope.resolve_local_variable(expr.name, location(expr))) {
				return sst::expr::var_local(local->address);
			}
		}
		
		if(auto def = scope.resolve_definiton(expr.name, expr.namespaze)) {
			return sst::expr::var_global(def->id);
		}

		if(auto glob = scope.resolve_global_variable(expr.name,	expr.namespaze)) {
			if(glob->is_private && glob->namespaze.is_inside_of(scope.get_namespace())) {
				throw CompilerError{"Cannot access private global varaible" , ast::location(expr)};
			} 
			return sst::expr::var_global(glob->id);
		}
		
		throw undefined_variable(expr);
	}



	sst::expr_ptr analyze_expr(const ast::expr::Member & access, Scope & scope) {
		const auto id = scope.resolve_member_id(access.name);
		auto expr = analyze_expression(*access.expr, scope);
		return sst::expr::member(std::move(expr), id);
	}
}