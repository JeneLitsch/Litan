#pragma once
#include <cstdint>
#include <vector>
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	class Heap;
}

namespace ltn::vm {
	class CombinedIterator {
	public:
		CombinedIterator(std::vector<Value> iters, Heap * heap);
		Value next();
		Value get();
		void move(std::int64_t amount);
		void mark();
		std::uint64_t size() const;
	private:
		std::vector<Value> iters;
		Heap * heap;
	};
}