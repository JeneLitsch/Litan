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
		StringIterator(Value ref);
		Value next(Heap &);
		Value get(Heap &);
		void move(Heap &, std::int64_t amount);
		void mark();
		std::uint64_t size(Heap & heap) const;
	private:
		Value ref;
		std::int64_t index;
	};
}