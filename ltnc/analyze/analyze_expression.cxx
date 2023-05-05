#include "analyze.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::ForwardDynamicCall & forward, Scope &) {
		
		std::vector<sst::expr_ptr> arguments;
		for(std::uint64_t i = 0; i < forward.arity; ++i) {
			arguments.push_back(std::make_unique<sst::Var>(i));
		}

		return std::make_unique<sst::Invoke>(
			std::make_unique<sst::Integer>(forward.address),
			std::move(arguments)
		);
	}



	// compiles any expr
	sst::expr_ptr analyze_expression(const ast::Expression & expr, Scope & scope) {
		return ast::visit_expression(expr, [&](const auto & e) {
			return analyze_expr(e, scope);
		});
	}
}