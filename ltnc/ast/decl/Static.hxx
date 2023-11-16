#pragma once
#include "Declaration.hxx"

namespace ltn::c::ast::decl {
	struct Static : public Declaration {
		Static(
			const SourceLocation & location,
			const std::string & name,
			const Namespace & namespaze);
		
		std::uint64_t id;
		
		const std::string & get_resolve_name() const;
		const Namespace & get_resolve_namespace() const;

		bool is_extern = false;
		bool is_private = false;
	private:
		static inline std::uint64_t counter = 0;
	};
}

