#pragma once
#include <cstdint>
#include <vector>
#include "ltnvm/Value.hxx"
#include "Iterator.hxx"

namespace ltn::vm {
	class Heap;
}

namespace ltn::vm {
	class CombinedIterator : public Iterator {
	public:
		CombinedIterator(std::vector<Value> iters, Heap * heap);
		
		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;
	private:
		std::vector<Value> iters;
		Heap * heap;
	};
}