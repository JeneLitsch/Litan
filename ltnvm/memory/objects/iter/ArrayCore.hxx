#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class ArrayCore {
	public:
		ArrayCore(std::uint64_t ref);
		Value next(Heap &);
		Value get(Heap &);
		void mark(Heap &);
	private:
		std::uint64_t ref;
		std::uint64_t index;
	};
}