#pragma once
#include "Static.hxx"

namespace ltn::c::sst::decl {
	struct Global final : public Static {
		Global(
			const std::string & name,
			const Namespace & namespaze,
			expr_ptr expr,
			std::uint64_t id);

		virtual ~Global();

		expr_ptr expr;
	};

	std::unique_ptr<Global> variable(
		const std::string & name,
		const Namespace & namespaze,
		expr_ptr expr,
		std::uint64_t id);
}