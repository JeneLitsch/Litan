#pragma once
#include "Static.hxx"

namespace ltn::c::sst::decl {
	struct Definition final : public Static {
		Definition(
			const std::string & name,
			const Namespace & namespaze,
			expr_ptr expr,
			std::uint64_t id);
		
		virtual ~Definition();
			
		expr_ptr expr;
	};

	std::unique_ptr<Definition> definition(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id);
}