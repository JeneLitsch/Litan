#include "Type.hxx"

namespace ltn::c::ast::expr {
	Type::Type(Variant variant, const SourceLocation & location)
		: Expression{location}
		, variant{std::move(variant)}  {}
	


	void Type::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Type> type(const SourceLocation & location, Type::Variant variant) {
		return std::make_unique<Type>(std::move(variant), location);
	}
}