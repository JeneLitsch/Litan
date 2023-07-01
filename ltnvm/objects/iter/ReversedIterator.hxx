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
		ReversedIterator(Value ref);
		Value next();
		Value get();
		void move(std::int64_t amount);
		void mark();
		std::uint64_t size() const;
	private:
		Value ref;
	};
}