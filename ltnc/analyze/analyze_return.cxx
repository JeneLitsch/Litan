#include "analyze.hxx"
#include <iostream>
#include "ltnc/ast/stmt/Return.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Return.hxx"
#include "ltnc/sst/stmt/CoReturn.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::Return & ret, Scope & scope) {
		auto expr = ret.expr ? analyze_expression(*ret.expr, scope) : sst::expr::null();
		if(scope.is_coroutine()) {
			return sst::stmt::co_retvrn(std::move(expr));
		}
		else {
			return sst::stmt::r3turn(std::move(expr), scope.get_return());
		}
	}
}