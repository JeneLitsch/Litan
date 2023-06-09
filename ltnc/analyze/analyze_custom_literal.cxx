#include "analyze.hxx"

namespace ltn::c {
	sst::expr_ptr analyze_expr(const ast::CustomLiteral & literal, Scope &) {
		return std::make_unique<sst::String>(literal.type + " " + literal.value);
	}
}