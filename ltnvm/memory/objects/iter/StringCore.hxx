#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class StringCore : public IteratorCore {
	public:
		StringCore(std::uint64_t ref);
		virtual Value next(Heap &) override;
		virtual void mark(Heap &) override;
	private:
		std::uint64_t ref;
		std::uint64_t index;
	};
}