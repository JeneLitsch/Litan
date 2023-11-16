#pragma once
#include "Binding.hxx"

namespace ltn::c::ast::bind {
	struct Group final : public Binding {
		Group(const SourceLocation & location);
		virtual void accept(const BindVisitor & visitor) const override;
		
		std::vector<bind_ptr> sub_bindings;
	};

	std::unique_ptr<Group> group(const SourceLocation & location);
};