#include "Binary.hxx"

namespace ltn::c::ast::expr {
	Binary::Binary(Op op, expr_ptr l, expr_ptr r, const SourceLocation & location)
		: Expression(location)
		, op(op)
		, l(std::move(l))
		, r(std::move(r)) {}



	void Binary::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Binary> binary(Binary::Op op, expr_ptr l, expr_ptr r, const SourceLocation & location) {
		return std::make_unique<Binary>(op, std::move(l), std::move(r), location);
	}
}