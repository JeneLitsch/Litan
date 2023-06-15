#pragma once
#include <cstdint>
#include "type_check.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	inline std::int64_t to_index(const Value value, std::uint64_t size) {
		if(!is_int(value)) throw Exception{
			Exception::Type::OUT_OF_RANGE,
			"Expected integer as index"
		};

		const auto index = ( value.i < 0) ?  value.i + size :  value.i;
		if(index < 0) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Negative index is not allowed"};
		}
		if(index >= size) {
			throw Exception{Exception::Type::OUT_OF_RANGE, "Index out of range"};
		}
		return index; 
	}
}