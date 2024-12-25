#include "analyze.hxx"
#include <iostream>
#include "litan_compiler/ast/stmt/Yield.hxx"
#include "litan_compiler/sst/expr/Literal.hxx"
#include "litan_compiler/sst/stmt/Yield.hxx"

namespace ltn::c {
	sst::stmt_ptr analyze_stmt(const ast::stmt::Yield & yield, Scope & scope) {
		if(scope.is_coroutine()) {
			auto expr = yield.expr ? analyze_expression(*yield.expr, scope) : sst::expr::null();
			return sst::stmt::yield(std::move(expr));
		}
		throw CompilerError { "Cannot used yield in non-coroutine.", ast::location(yield) };
	}
}