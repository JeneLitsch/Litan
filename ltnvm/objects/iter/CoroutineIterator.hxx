#pragma once
#include <cstdint>
#include "ltnvm/Value.hxx"
#include "Iterator.hxx"

namespace ltn::vm {
	class Coroutine;
	class VMCore;
	class CoroutineIterator : public Iterator {
	public:
		CoroutineIterator(Coroutine * coroutine, VMCore * core);
		CoroutineIterator(std::nullptr_t, VMCore * core);

		virtual Value next() override;
		virtual Value get() override;
		virtual void move(std::int64_t amount) override;
		virtual void mark() override;
		virtual std::uint64_t size() const override;
		virtual std::unique_ptr<Iterator> clone() const override;

	private:
		Value coroutine;
		VMCore * core;
	};
}