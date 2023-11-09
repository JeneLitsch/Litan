#pragma once
#include "Static.hxx"

namespace ltn::c::sst {
	struct Global final : public Static {
		Global(
			const std::string & name,
			const Namespace & namespaze,
			std::unique_ptr<sst::expr::Expression> expr,
			std::uint64_t id);

		virtual ~Global();

		std::unique_ptr<sst::expr::Expression> expr;
	};
}