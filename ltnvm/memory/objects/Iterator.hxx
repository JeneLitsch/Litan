#pragma once
#include <cstdint>

namespace ltn::vm {
	struct Iterator {
		struct Range {
			std::int64_t begin;
			std::int64_t end;
			std::int64_t step;
			std::int64_t current;
		};

		enum class Type {
			RANGE
		};

		Type type;

		union {
			Range range;
		};
		
	};


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
	}
}