#pragma once
#include <cstdint>
#include "type_check.hxx"
#include "Exception.hxx"

namespace ltn::vm {
	void guard_index(const auto & collection, auto i) {
		if(i < 0) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Negative index is not allowed"};
		}
		if(i >= static_cast<decltype(i)>(collection.size())) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Index out of range"};
		}
	}

	inline std::int64_t to_index(const Value value) {
		if(!is_int(value)) {
			throw Exception{Exception::Type::OUT_OF_RANGE,"Expected integer as index"};
		}
		return value.i;
	}
}