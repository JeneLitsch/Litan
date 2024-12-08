#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"
#include "Contiguous.hxx"

namespace ltn::vm {
	struct Tuple : Contiguous {
		Tuple() 
			: Contiguous{} {};

		Tuple(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};

		virtual Value get_member(std::uint64_t id) const override;
	};

	inline Tuple clone(const Tuple & tup) {
		return tup;
	}
}