#include "analyze.hxx"
#include <iostream>
#include <sstream>
#include "stdxx/functional.hxx"
#include "ltnc/sst/expr/Binary.hxx"

namespace ltn::c {
	// compiles a binary operation
	sst::expr_ptr analyze_expr(
		const ast::Binary & binary,
		Scope & scope) {
		
		auto l = analyze_expression(*binary.l, scope);
		auto r = analyze_expression(*binary.r, scope);
		const auto op = binary.op;

		return sst::expr::binary(op, std::move(l), std::move(r));
	}
}