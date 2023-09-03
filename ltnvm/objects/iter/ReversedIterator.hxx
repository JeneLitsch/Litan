#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"
#include "Iterator.hxx"

namespace ltn::vm {
	struct VMCore;
	class Heap;
}

namespace ltn::vm {
	class ReversedIterator : public Iterator {
	public:
		ReversedIterator(Value ref);
		
		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;
	private:
		Value ref;
	};
}