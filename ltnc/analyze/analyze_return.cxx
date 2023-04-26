#include "analyze.hxx"
#include "conversion.hxx"
#include <iostream>

namespace ltn::c {

	sst::stmt_ptr analyze_stmt(const ast::Return & ret, Scope & scope) {
		
		const auto return_type = scope.get_return_type();
		
		auto return_value = ret.expr 
			? analyze_expression(*ret.expr, scope)
			: std::make_unique<sst::Null>(type::Null{});
		
		auto expr = conversion_on_return(
			std::move(return_value),
			return_type,
			location(ret)
		);
		
		return std::make_unique<sst::Return>(
			std::move(expr),
			scope.get_return()
		);
	}
}