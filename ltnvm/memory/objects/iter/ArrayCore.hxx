#pragma once
#include <cstdint>
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm::iter {
	class ArrayCore {
	public:
		ArrayCore(std::uint64_t ref);
		Value next(Heap &);
		Value get(Heap &);
		void move(Heap &, std::uint64_t amount);
		void mark(Heap &);
	private:
		std::uint64_t ref;
		std::uint64_t index;
	};
}