#include "Choose.hxx"

namespace ltn::c::ast::expr {
	Choose::Choose(const SourceLocation & location)
		: Expression{location} {}



	void Choose::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Choose> sw1tch(const SourceLocation & location) {
		return std::make_unique<Choose>(location);
	}
}