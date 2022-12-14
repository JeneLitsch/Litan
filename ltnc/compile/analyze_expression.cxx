#include "compile.hxx"


namespace ltn::c {
	
	sst::expr_ptr analyze_expr(
		const ast::DeclType & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		auto result = analyze_expression(*expr.expression, info, scope);
		const auto type = result->type;
		const auto name_addr = info.member_table.get_id("name");

		return std::make_unique<sst::DeclType>(
			name_addr,
			std::move(result),
			type
		);
	}



	// compiles any expression
	sst::expr_ptr analyze_expression(
		const ast::Expression & expr,
		CompilerInfo & info,
		Scope & scope) {
		
		return ast::visit_expression(expr, [&](const auto & e) -> sst::expr_ptr {
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