#include "Index.hxx"

namespace ltn::c::ast::expr {
	Index::Index(
		expr_ptr expr,
		expr_ptr index,
		const SourceLocation & location)
		: Expression(location)
		, expr(std::move(expr))
		, index(std::move(index)) {}



	void Index::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Index> index(const SourceLocation & location, expr_ptr expr, expr_ptr index) {
		return std::make_unique<Index>(std::move(expr), std::move(index), location);
	}
}