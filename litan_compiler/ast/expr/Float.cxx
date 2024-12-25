#include "Float.hxx"

namespace ltn::c::ast::expr {
	Float::Float(stx::float64_t value, const SourceLocation & location)
		: Expression(location), value(value) {}
		


	void Float::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Float> floating(stx::float64_t value, const SourceLocation & location) {
		return std::make_unique<Float>(value, location);
	}
}