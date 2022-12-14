#include "compile.hxx"
#include "ltnc/type/check.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(
			sst::Unary::Op op,
			const type::Type & x) {
			using OP = sst::Unary::Op;
			switch (op) {
				case OP::NEG:    return type::deduce_neg(x);
				case OP::NOT:    return type::deduce_not(x);
				case OP::NUL:    return type::deduce_nulltest(x);
				case OP::BITNOT: return type::deduce_bitnot(x);
				case OP::DEREF:  return type::deduce_deref(x);
			}
		}
	}


	sst::expr_ptr analyze_expr(
		const ast::Unary & unary,
		CompilerInfo & info,
		Scope & scope) {
		
		using Op = ast::Unary::Type;
		const auto expr = analyze_expression(*unary.expression, info, scope);
		const auto op = static_cast<sst::Unary::Op>(unary.type);
		const auto type = deduce_type(op, expr->type);
		return std::make_unique<sst::Unary>(op, std::move(expr), type);
	}
}