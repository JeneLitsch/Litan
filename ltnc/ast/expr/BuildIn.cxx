#include "BuildIn.hxx"

namespace ltn::c::ast::expr {
	BuildIn::BuildIn(
		std::string key,
		const SourceLocation & location)
		: Expression{location}
		, key{std::move(key)} {}

	
	
	void BuildIn::accept(const ExprVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<BuildIn> build_in(const SourceLocation & location, std::string key) {
		return std::make_unique<BuildIn>(key, location);
	}
}