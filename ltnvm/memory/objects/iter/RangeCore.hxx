#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class RangeCore {
	public:
		RangeCore(std::int64_t begin, std::int64_t end, std::int64_t step);
		Value next(Heap &);
		Value get(Heap &);
		void mark(Heap &) {}
	private:
		std::int64_t begin;
		std::int64_t end;
		std::int64_t step;
		std::int64_t current;
	};
}