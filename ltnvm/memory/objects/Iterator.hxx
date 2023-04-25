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

		struct String {
			std::uint64_t string;
			std::uint64_t index;
		};
		

		enum class Type {
			RANGE, ARRAY, STRING,
		};

		Type type;

		union {
			Range range;
			Array array;
			String string;
		};
		
	};


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(std::uint64_t array);
		Iterator string(std::uint64_t string);
	}
}