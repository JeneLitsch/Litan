#pragma once
#include <cstdint>
#include "litan_vm/Value.hxx"
#include "Iterator.hxx"
#include "litan_vm/objects/container/String.hxx"

namespace ltn::vm {
	class StringIterator : public Iterator {
	public:
		StringIterator(String * string);
		
		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;
	private:
		String * string;
		std::int64_t index;
	};
}