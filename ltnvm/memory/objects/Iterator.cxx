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
	}
}