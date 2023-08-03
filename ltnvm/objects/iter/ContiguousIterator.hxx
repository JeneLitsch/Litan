#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"
#include "Iterator.hxx"
#include "ltnvm/objects/container.hxx"

namespace ltn::vm {
	class ContiguousIterator : public Iterator {
	public:
		ContiguousIterator(Contiguous * container);

		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;

	private:
		Contiguous * container;
		std::int64_t index;
	};
}