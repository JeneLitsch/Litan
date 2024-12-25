#include "Tuple.hxx"

namespace ltn::c::ast::expr {
	Tuple::Tuple(
		const SourceLocation & location,
		std::vector<expr_ptr> elements)
		: Expression(location)
		, elements{std::move(elements)} {}



	void Tuple::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Tuple> tuple(const SourceLocation & location, std::vector<expr_ptr> elements) {
		return std::make_unique<Tuple>(location, std::move(elements));
	}
}