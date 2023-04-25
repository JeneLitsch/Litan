#pragma once
#include <cstdint>
#include <memory>
#include "iter/IteratorCore.hxx"

namespace ltn::vm {
	struct Iterator {
	public:
		Iterator(std::unique_ptr<iter::IteratorCore> core)
			: core {std::move(core)} {}
		Value next(Heap & heap) { return core->next(heap); }
		void mark(Heap & heap) { return core->mark(heap); }
	private:
		std::unique_ptr<iter::IteratorCore> core;
	};


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(std::uint64_t array);
		Iterator string(std::uint64_t string);

		Value wrap(const Value & ref, Heap & heap);
		Value next(const Value & ref, Heap & heap);
	}
}