#pragma once
#include <atomic>
#include <cstdint>

namespace stx {
	
	class unique {
	public:
		unique() : value(counter++) {}

		std::uint64_t operator*() const {
			return value;
		}
	private:
		std::uint64_t value;
		static inline std::atomic<std::uint64_t> counter = 0;
	};
}