#include "Unary.hxx"

namespace ltn::c::ast::expr {
	Unary::Unary(Op op, expr_ptr expr, const SourceLocation & location)
		: Expression(location)
		, op(op)
		, expr(std::move(expr)) {}



	void Unary::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Unary> unary(const SourceLocation & location, Unary::Op op, expr_ptr expr) {
		return std::make_unique<Unary>(op, std::move(expr), location);
	}
}