#include "analyze.hxx"
#include <iostream>
#include "ltnc/ast/stmt/Return.hxx"
#include "ltnc/ast/stmt/Yield.hxx"
#include "ltnc/sst/expr/Literal.hxx"
#include "ltnc/sst/stmt/Return.hxx"
#include "ltnc/sst/stmt/Yield.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::Return & ret, Scope & scope) {
		auto expr = ret.expr ? analyze_expression(*ret.expr, scope) : sst::expr::null();
		return sst::stmt::r3turn(std::move(expr), scope.get_return());
	}



	sst::stmt_ptr analyze_stmt(const ast::stmt::Yield & yield, Scope & scope) {
		auto expr = yield.expr ? analyze_expression(*yield.expr, scope) : sst::expr::null();
		return sst::stmt::yield(std::move(expr), scope.get_return());
	}
}