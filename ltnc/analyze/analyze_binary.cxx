#include "analyze.hxx"
#include <iostream>
#include <sstream>
#include "stdxx/functional.hxx"
#include "ltnc/ast/expr/Binary.hxx"
#include "ltnc/sst/expr/Binary.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::Binary & binary, Scope & scope) {
		
		auto l = analyze_expression(*binary.l, scope);
		auto r = analyze_expression(*binary.r, scope);
		const auto op = binary.op;

		return sst::expr::binary(op, std::move(l), std::move(r));
	}
}