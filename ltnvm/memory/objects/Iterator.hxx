#pragma once
#include <cstdint>
#include <memory>
#include "iter/IteratorCore.hxx"

namespace ltn::vm {
	struct Iterator {
		struct Concept {
			virtual Value next(Heap & heap) = 0;
			virtual void mark(Heap & heap) = 0;
			virtual ~Concept() = default;
		};

		template<typename T>
		struct Impl : Concept {
			Impl(T && t) : t {std::move(t)} {}
			virtual Value next(Heap & heap) { return t.next(heap); }
			virtual void mark(Heap & heap) { return t.mark(heap); }
			T t;
		};
	public:
		template<typename T>
		Iterator(T && impl) : core { std::make_unique<Impl<T>>(std::move(impl)) } {}
		Value next(Heap & heap) { return core->next(heap); }
		void mark(Heap & heap) { return core->mark(heap); }
	private:
		std::unique_ptr<Concept> core;
	};


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(std::uint64_t array);
		Iterator string(std::uint64_t string);

		Value wrap(const Value & ref, Heap & heap);
		Value next(const Value & ref, Heap & heap);
	}
}