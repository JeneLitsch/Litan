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

		struct Array {
			std::uint64_t array;
			std::uint64_t index;
		};
		

		enum class Type {
			RANGE, ARRAY
		};

		Type type;

		union {
			Range range;
			Array array;
		};
		
	};


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(std::uint64_t array);
	}
}