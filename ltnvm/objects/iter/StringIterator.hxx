#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm {
	class StringIterator  {
	public:
		StringIterator(std::uint64_t ref);
		Value next(Heap &);
		Value get(Heap &);
		void move(Heap &, std::int64_t amount);
		void mark(Heap &);
	private:
		std::uint64_t ref;
		std::int64_t index;
	};
}