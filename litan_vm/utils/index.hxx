#pragma once
#include <cstdint>
#include "type_check.hxx"
#include "litan_vm/Exception.hxx"

namespace ltn::vm {
	inline std::int64_t to_index(const Value value, std::int64_t size) {
		if(!is_int(value)) throw Exception{
			Exception::Type::OUT_OF_RANGE,
			"Expected integer as index"
		};

		const auto wrap = static_cast<std::int64_t>(size) * (value.i < 0);
		const auto index = value.i + wrap;
		if(index < 0) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Negative index is not allowed"};
		}
		if(index >= size) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Index out of range"};
		}
		return index; 
	}
}