#include "analyze.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::CustomLiteral & literal, Scope & scope) {
		return scope.resolve_custom_literal(literal.type, literal.value);
	}
}