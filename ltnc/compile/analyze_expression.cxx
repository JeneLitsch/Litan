#include "compile.hxx"


namespace ltn::c {
	
	sst::expr_ptr analyze_expr(
		const ast::DeclType & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		const auto result = analyze_expression(*expr.expression, info, scope);
		const auto type = result->type;

		return std::make_unique<sst::DeclType>(std::move(result), type);
	}



	// compiles any expression
	sst::expr_ptr analyze_expression(
		const ast::Expression & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		return ast::visit_expression(expr, [&](const auto & e) {
			return analyze_expr(e, info, scope);
		});
	}



	void guard_const(const ast::Node & node, const Scope & scope) {
		if(scope.is_const()) {
			throw CompilerError{
				"Cannot modify or reassign variable in const function",
				node.location};
		}
	}
}