#pragma once
#include <cstdint>
#include <string>

namespace ltn::vm {
	struct Type;
	struct Value;
	class Heap;

	bool type_is(const std::uint8_t * code, const Value & value, Heap & heap);
	bool type_is(const Type & type, const Value & value, Heap & heap);
}