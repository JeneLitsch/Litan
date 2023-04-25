#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class StringCore  {
	public:
		StringCore(std::uint64_t ref);
		Value next(Heap &);
		void mark(Heap &);
	private:
		std::uint64_t ref;
		std::uint64_t index;
	};
}