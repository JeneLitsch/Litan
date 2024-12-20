#pragma once
#include "Expression.hxx"

namespace ltn::c::sst::expr {
	struct BuildIn final : ExpressionCRTP<BuildIn> {
		BuildIn(std::string key);
		virtual ~BuildIn();

		virtual std::uint64_t alloc() const override;

		std::string key;
	};

	std::unique_ptr<BuildIn> build_in(std::string key);
}