#include "Reflect.hxx"

namespace ltn::c::ast::expr {
	Reflect::Reflect(
		Query query,
		const SourceLocation & location)
		: Expression(location)
		, query{std::move(query)} {}
		


	void Reflect::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Reflect> reflect(const SourceLocation & location, Reflect::Query query) {
		return std::make_unique<Reflect>(query, location);
	}
}