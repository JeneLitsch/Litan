#pragma once
#include <cstdint>
#include "TypeCheck.hxx"
#include "memory/Register.hxx"

namespace ltn::vm {
	void guard_index(const auto & collection, auto i) {
		if(i < 0) {
			throw std::runtime_error{"Negative index is not allowed"};
		}
		if(i >= static_cast<decltype(i)>(collection.size())) {
			throw std::runtime_error{"Index out of range"};
		}
	}

	inline std::int64_t to_index(const Value value) {
		if(!is_int(value)) {
			throw std::runtime_error{"Expected integer as index"};
		}
		return value.i;
	}
}