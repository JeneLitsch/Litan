#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm {
	class RangeIterator {
	public:
		RangeIterator(std::int64_t begin, std::int64_t end, std::int64_t step);
		Value next();
		Value get();
		void move(std::int64_t amount);
		void mark() {}
		std::uint64_t size() const;
	private:
		std::int64_t begin;
		std::int64_t end;
		std::int64_t step;
		std::int64_t current;
	};
}