#include "CustomLiteral.hxx"

namespace ltn::c::ast::expr {
	CustomLiteral::CustomLiteral(
		std::string type,
		std::string value,
		const SourceLocation & location)
		: Expression{location}
		, type{std::move(type)}
		, value{std::move(value)} {}



	void CustomLiteral::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<CustomLiteral> custom_literal(const SourceLocation & location, std::string type, std::string value) {
		return std::make_unique<CustomLiteral>(std::move(type), std::move(value), location);
	}
}