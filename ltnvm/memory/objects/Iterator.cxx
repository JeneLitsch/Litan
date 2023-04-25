#include "Iterator.hxx"

namespace ltn::vm {
	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step) {
			return Iterator {
				.type = Iterator::Type::RANGE,
				.range = Iterator::Range {
					.begin = begin,
					.end = end,
					.step = step,
					.current = begin,
				},
			};
		}



		Iterator array(std::uint64_t array) {
			return Iterator {
				.type = Iterator::Type::ARRAY,
				.array = Iterator::Array {
					.array = array,
					.index = 0,
				},
			};
		}



		Iterator string(std::uint64_t string) {
			return Iterator {
				.type = Iterator::Type::STRING,
				.string = Iterator::String {
					.string = string,
					.index = 0,
				},
			};
		}
	}
}