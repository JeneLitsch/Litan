#include "Bool.hxx"

namespace ltn::c::ast::expr {
	Bool::Bool(bool value, const SourceLocation & location)
		: Expression(location), value(value) {}



	void Bool::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Bool> boolean(bool value, const SourceLocation & location) {
		return std::make_unique<Bool>(value, location);
	}



	std::unique_ptr<Bool> boolean_false(const SourceLocation & location) {
		return boolean(false, location);
	}



	std::unique_ptr<Bool> boolean_true(const SourceLocation & location) {
		return boolean(true, location);
	}
}