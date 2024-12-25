#pragma once
#include <cstdint>
#include "litan_vm/Value.hxx"
#include "Iterator.hxx"

namespace ltn::vm {
	struct VMCore;
	class Heap;
}

namespace ltn::vm {
	class RangeIterator : public Iterator {
	public:
		RangeIterator(std::int64_t begin, std::int64_t end, std::int64_t step);
		
		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override {} 
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;
	private:
		std::int64_t begin;
		std::int64_t end;
		std::int64_t step;
		std::int64_t current;
	};
}