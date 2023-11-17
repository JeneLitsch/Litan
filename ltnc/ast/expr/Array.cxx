#include "Array.hxx"

namespace ltn::c::ast::expr {
	Array::Array(
		const SourceLocation & location,
		std::vector<expr_ptr> elements)
		: Expression(location)
		, elements{std::move(elements)} {}



	void Array::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Array> array(const SourceLocation & location, std::vector<expr_ptr> elements) {
		return std::make_unique<Array>(location, std::move(elements));
	}
}