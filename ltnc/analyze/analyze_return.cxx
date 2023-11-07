#include "analyze.hxx"
#include <iostream>
#include "ltnc/sst/expr/Literal.hxx"

namespace ltn::c {

	sst::stmt_ptr analyze_stmt(const ast::Return & ret, Scope & scope) {
		
		auto expr = ret.expr 
			? analyze_expression(*ret.expr, scope)
			: std::make_unique<sst::Null>();
		
		return std::make_unique<sst::Return>(
			std::move(expr),
			scope.get_return()
		);
	}
}