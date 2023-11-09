#pragma once
#include "Static.hxx"

namespace ltn::c::sst {
	struct Definition final : public Static {
		Definition(
			const std::string & name,
			const Namespace & namespaze,
			std::unique_ptr<sst::expr::Expression> expr,
			std::uint64_t id);
		
		virtual ~Definition();
			
		std::unique_ptr<sst::expr::Expression> expr;
	};
}