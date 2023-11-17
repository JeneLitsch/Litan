#include "Char.hxx"

namespace ltn::c::ast::expr {
	Char::Char(std::uint8_t value, const SourceLocation & location)
		: Expression(location), value(value) {}



	void Char::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Char> character(const SourceLocation & location, std::uint8_t value) {
		return std::make_unique<Char>(value, location);
	}
}