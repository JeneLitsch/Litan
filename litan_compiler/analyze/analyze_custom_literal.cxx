#include "analyze.hxx"
#include "litan_compiler/ast/expr/CustomLiteral.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::expr::CustomLiteral & literal, Scope & scope) {
		return scope.resolve_custom_literal(literal.type, literal.value);
	}
}