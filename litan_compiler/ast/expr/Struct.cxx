#include "Struct.hxx"

namespace ltn::c::ast::expr {
	Struct::Struct(const SourceLocation & location)
		: Expression{location} {}
	


	void Struct::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Struct> strukt(const SourceLocation & location) {
		return std::make_unique<Struct>(location);
	}
}