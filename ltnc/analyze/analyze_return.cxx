#include "analyze.hxx"
#include <iostream>
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Return.hxx"

namespace ltn::c {

	sst::stmt_ptr analyze_stmt(const ast::Return & ret, Scope & scope) {
		auto expr = ret.expr ? analyze_expression(*ret.expr, scope) : sst::expr::null();
		return sst::r3turn(std::move(expr), scope.get_return());
	}
}