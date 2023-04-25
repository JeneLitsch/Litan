#pragma once
#include "IteratorCore.hxx"

namespace ltn::vm::iter {
	class RangeCore : public IteratorCore {
	public:
		RangeCore(std::int64_t begin, std::int64_t end, std::int64_t step);
		virtual Value next(Heap &) override;
		virtual void mark(Heap &) override {}
	private:
		std::int64_t begin;
		std::int64_t end;
		std::int64_t step;
		std::int64_t current;
	};
}