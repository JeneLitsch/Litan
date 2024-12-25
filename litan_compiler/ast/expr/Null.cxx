#include "Null.hxx"

namespace ltn::c::ast::expr {
	Null::Null(const SourceLocation & location)
		: Expression(location) {}



	void Null::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Null> null(const SourceLocation & location) {
		return std::make_unique<Null>(location);
	}
}