#pragma once
#include <cstdint>
#include <memory>
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm {
	class Heap;

	struct Iterator {
		struct Concept {
			virtual Value next(Heap & heap) = 0;
			virtual Value get(Heap & heap) = 0;
			virtual void move(Heap & heap, std::int64_t amount) = 0;
			virtual void mark(Heap & heap) = 0;
			virtual std::unique_ptr<Concept> clone() = 0;
			virtual ~Concept() = default;
		};

		template<typename T>
		struct Impl : Concept {
			template<typename U>
			Impl(U && t) : t {std::move(t)} {}
			virtual Value next(Heap & heap) override { 
				return t.next(heap);
			}

			virtual Value get(Heap & heap) override {
				return t.get(heap);
			}
			
			virtual void move(Heap & heap, std::int64_t amount) override { 
				return t.move(heap, amount);
			}
			
			virtual void mark(Heap & heap) override {
				return t.mark(heap);
			}
			
			virtual std::unique_ptr<Concept> clone() override {
				return std::make_unique<Impl<T>>(t);
			}

			T t;
		};
	public:
		template<typename T>
		Iterator(T && impl) : core { std::make_unique<Impl<T>>(Impl<T>{std::move(impl)}) } {}
		Value next(Heap & heap) { return core->next(heap); }
		Value get(Heap & heap) { return core->get(heap); }
		void move(Heap & heap, std::int64_t amount) { return core->move(heap, amount); }
		void mark(Heap & heap) { return core->mark(heap); }

		Iterator clone() const { return Iterator{core->clone()}; }
	private:
		Iterator(std::unique_ptr<Concept> core) : core { std::move(core) } {}

		std::unique_ptr<Concept> core;
	};



	Iterator clone(const Iterator & iter);


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(std::uint64_t array);
		Iterator string(std::uint64_t string);

		Value wrap(const Value & ref, Heap & heap);
		Value next(const Value & ref, Heap & heap);
		Value get(const Value & ref, Heap & heap);
		void move(const Value & ref, const Value & amount, Heap & heap);
	}
}