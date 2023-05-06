#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	class Heap;

	struct Type {
		std::vector<std::uint8_t> code;
	};

	inline Type clone(const Type & type) {
		return type;
	}

	std::string to_type_name(const std::uint8_t * code);
	std::string to_type_name(const Type & type);

	bool type_is(const std::uint8_t * code, const Value & value, Heap & heap);
	bool type_is(const Type & type, const Value & value, Heap & heap);
	Value type_cast(const std::uint8_t * code, const Value & value, Heap & heap);
	Value type_cast(const Type & type, const Value & value, Heap & heap);
}