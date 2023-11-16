#pragma once
#include "Declaration.hxx"

namespace ltn::c::ast::decl {
	struct Enumeration final : Declaration {
		struct Label {
			std::string name;
			std::int64_t value;
		};
		
		Enumeration(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze,
			std::vector<Label> labels);

		virtual ~Enumeration();
		
		std::vector<Label> labels;
	};

	std::unique_ptr<Enumeration> enumeration(
		const SourceLocation & location,
		const std::string & name,
		const Namespace & namespaze,
		std::vector<Enumeration::Label> labels
	);
}