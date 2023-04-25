#pragma once
#include <cstdint>
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm::iter {
	class RangeCore {
	public:
		RangeCore(std::int64_t begin, std::int64_t end, std::int64_t step);
		Value next(Heap &);
		Value get(Heap &);
		void move(Heap &, std::int64_t amount);
		void mark(Heap &) {}
	private:
		std::int64_t begin;
		std::int64_t end;
		std::int64_t step;
		std::int64_t current;
	};
}