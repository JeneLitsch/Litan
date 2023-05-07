#pragma once
#include <cstdint>
#include <string>

namespace ltn::vm {
	struct Type;
	struct Value;
	class Heap;

	Value type_cast(const std::uint8_t * code, const Value & value, Heap & heap);
	Value type_cast(const Type & type, const Value & value, Heap & heap);
}