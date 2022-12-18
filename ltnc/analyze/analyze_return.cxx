#include "analyze.hxx"
#include "conversion.hxx"
#include <iostream>

namespace ltn::c {
	// compiles -> return...;
	sst::stmt_ptr analyze_stmt(
		const ast::Return & ret,
		Context & context,
		Scope & scope) {
		
		const auto return_type = scope.get_return_type();
		if(ret.expression) {
			auto expr = conversion_on_return(analyze_expression(*ret.expression, context, scope), return_type, ret.location);
			return std::make_unique<sst::Return>(0, false, std::move(expr), scope.get_return());
		}
		else {
			auto expr = conversion_on_return(std::make_unique<sst::Null>(type::Null{}), return_type, ret.location);
			return std::make_unique<sst::Return>(0, false, std::move(expr), scope.get_return());
		}
	}
}