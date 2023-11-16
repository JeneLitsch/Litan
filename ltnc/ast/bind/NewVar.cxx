#include "NewVar.hxx"

namespace ltn::c::ast::bind {
	NewVar::NewVar(const SourceLocation & location, std::string name)
		: Binding {location}
		, name{std::move(name)} {}



	void NewVar::accept(const BindVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<NewVar> new_local(const SourceLocation & location, std::string name) {
		return std::make_unique<NewVar>(location, std::move(name));
	}
}