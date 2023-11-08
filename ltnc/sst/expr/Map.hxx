#pragma once
#include "Expression.hxx"
#include <vector>

namespace ltn::c::sst {
	struct Map final : public ExpressionCRTP<Map> {
		struct Pair {
			expr_ptr key;
			expr_ptr val;
		};

		Map();

		virtual std::uint64_t alloc() const override;

		std::vector<Pair> pairs;
	};

	std::unique_ptr<Map> map();
}