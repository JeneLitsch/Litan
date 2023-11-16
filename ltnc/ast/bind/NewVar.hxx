#pragma once
#include "Binding.hxx"

namespace ltn::c::ast::bind {
	struct NewVar final : public Binding {
		NewVar(const SourceLocation & location, std::string name);
		virtual void accept(const BindVisitor & visitor) const override;

		std::string name;
	};

	std::unique_ptr<NewVar> new_local(const SourceLocation & location, std::string name);
}