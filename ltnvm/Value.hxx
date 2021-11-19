#pragma once
#include <cstdint>

namespace ltn::vm {
	struct Value {
		enum class Type : std::uint32_t {
			INT, FLOAT, BOOL, ARRAY, MAP, INTERNAL, NVLL,
		};
		union {
			std::uint64_t u;
			std::int64_t i;
			double f;
			bool b;
		};
		Type type = Type::INTERNAL;
	};	
}