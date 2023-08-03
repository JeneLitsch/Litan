#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct Tuple : Contiguous {
		Tuple() 
			: Contiguous{} {};

		Tuple(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};
	};

	inline Tuple clone(const Tuple & tup) {
		return tup;
	}
}