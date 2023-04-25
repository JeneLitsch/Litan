#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class ArrayCore : public IteratorCore {
	public:
		ArrayCore(std::uint64_t ref);
		virtual Value next(Heap &) override;
		virtual void mark(Heap &) override;
	private:
		std::uint64_t ref;
		std::uint64_t index;
	};
}