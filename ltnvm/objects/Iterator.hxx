#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"


namespace ltn::vm {
	class Heap;

	struct Iterator : public Object {
		struct Concept {
			virtual Value next() = 0;
			virtual Value get() = 0;
			virtual void move(std::int64_t amount) = 0;
			virtual void mark() = 0;
			virtual std::uint64_t size() const = 0;
			virtual std::unique_ptr<Concept> clone() = 0;
			virtual ~Concept() = default;
		};

		template<typename T>
		struct Impl : Concept {
			template<typename U>
			Impl(U && t) : t {std::move(t)} {}
			virtual Value next() override { 
				return t.next();
			}

			virtual Value get() override {
				return t.get();
			}
			
			virtual void move(std::int64_t amount) override { 
				return t.move(amount);
			}
			
			virtual void mark() override {
				return t.mark();
			}

			virtual std::uint64_t size() const override {
				return t.size();
			}
			
			virtual std::unique_ptr<Concept> clone() override {
				return std::make_unique<Impl<T>>(t);
			}

			T t;
		};
	public:
		template<typename T>
		Iterator(T && impl) : impl { std::make_unique<Impl<T>>(Impl<T>{std::move(impl)}) } {}
		Value next() { return impl->next(); }
		Value get() { return impl->get(); }
		void move(std::int64_t amount) { return impl->move(amount); }
		void mark() { return impl->mark(); }
		std::uint64_t size() const { return impl->size(); }

		Iterator clone() const { return Iterator{impl->clone()}; }
	private:
		Iterator(std::unique_ptr<Concept> impl) : impl { std::move(impl) } {}

		std::unique_ptr<Concept> impl;
	};



	Iterator clone(const Iterator & iter);


	namespace iterator {
		Iterator range(std::int64_t begin, std::int64_t end, std::int64_t step);
		Iterator array(Value array);
		Iterator string(Value string);
		Iterator combined(std::vector<Value> refs, Heap & heap);
		Iterator reversed(Value ref);

		Value wrap(const Value & ref, Heap & heap);
		Value next(const Value & ref);
		Value get(const Value & ref);
		void move(const Value & ref, const Value & amount);
		std::uint64_t size(const Value & ref);
	}
}