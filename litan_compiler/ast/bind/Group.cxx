#include "Group.hxx"

namespace ltn::c::ast::bind {
	Group::Group(const SourceLocation & location)
		: Binding {location} {}

	
	
	void Group::accept(const BindVisitor & visitor) const {
		visitor.visit(*this);
	}



	std::unique_ptr<Group> group(const SourceLocation & location) {
		return std::make_unique<Group>(location);
	}
}