#include "Var.hxx"

namespace ltn::c::ast::expr {
	Var::Var(
		const std::string & name,
		const Namespace & namespaze,
		const SourceLocation & location)
		: Expression(location)
		, name{name}
		, namespaze{namespaze} {}



	void Var::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Var> variable(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze) {
		
		return std::make_unique<Var>(name, namespaze, location);
	}
}