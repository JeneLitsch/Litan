#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	struct VmCore;
	class Heap;
}

namespace ltn::vm {
	class ReversedIterator {
	public:
		ReversedIterator(std::uint64_t ref, Heap & heap);
		Value next(Heap &);
		Value get(Heap &);
		void move(Heap &, std::int64_t amount);
		void mark(Heap &);
		std::uint64_t size(Heap & heap) const;
	private:
		std::uint64_t ref;
	};
}