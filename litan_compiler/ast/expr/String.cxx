#include "String.hxx"

namespace ltn::c::ast::expr {
	String::String(const std::string & value, const SourceLocation & location)
		: Expression(location), value(value) {}
		


	void String::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<String> string(const SourceLocation & location, const std::string & value) {
		return std::make_unique<String>(value, location);
	}
}