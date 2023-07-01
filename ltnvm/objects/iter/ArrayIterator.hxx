#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"

namespace ltn::vm {
	class ArrayIterator {
	public:
		ArrayIterator(Value ref);
		Value next();
		Value get();
		void move(std::int64_t amount);
		void mark();
		std::uint64_t size() const;
	private:
		Value ref;
		std::int64_t index;
	};
}