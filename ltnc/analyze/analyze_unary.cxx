#include "analyze.hxx"
#include "ltnc/type/traits.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c {
	namespace {
		type::Type deduce_type(
			sst::Unary::Op op,
			const type::Type & x) {
			using OP = UnaryOp;
			switch (op) {
				case OP::NEG:    return type::deduce_neg(x);
				case OP::NOT:    return type::deduce_not(x);
				case OP::NUL:    return type::deduce_nulltest(x);
				case OP::BITNOT: return type::deduce_bitnot(x);
				case OP::DEREF:  return type::deduce_deref(x);
				default: throw std::runtime_error{"Invalid Unary::Op"};
			}
		}


		
		CompilerError invalid_operands(
			const type::Type & type,
			const SourceLocation & location) {
			std::ostringstream oss;
			oss 
				<< "Invalid operands ("
				<< to_string(type)
				<< ") for unary expression";

			return CompilerError { oss.str(), location };
		}
	}



	sst::expr_ptr analyze_expr(
		const ast::Unary & unary,
		Context & context,
		Scope & scope) {
		
		auto expr = analyze_expression(*unary.expression, context, scope);
		const auto op = static_cast<sst::Unary::Op>(unary.op);
		const auto type = deduce_type(op, expr->type);

		if(is_error(type)) {
			throw invalid_operands(expr->type, unary.location);
		} 

		return std::make_unique<sst::Unary>(op, std::move(expr), type);
	}
}