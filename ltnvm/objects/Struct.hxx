#pragma once
#include <vector>
#include <utility>
#include "ltnvm/Value.hxx"
#include "ltn/MemberCode.hxx"

namespace ltn::vm {




	struct Struct {
		using Members = std::vector<std::pair<std::uint64_t, Value>>;
		Members members;
	};
	


	inline Struct clone(const Struct & strukt) {
		return strukt;
	}
}