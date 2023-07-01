#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class Heap;

	struct Iterator : public Object {
		virtual Value next() = 0;
		virtual Value get() = 0;
		virtual void move(std::int64_t amount) = 0;
		virtual void mark() = 0;
		virtual std::uint64_t size() const = 0;
		virtual std::unique_ptr<Iterator> clone() const = 0;
	};



	std::unique_ptr<Iterator> clone(const Iterator & iter);


	namespace iterator {
		std::unique_ptr<Iterator> range(std::int64_t begin, std::int64_t end, std::int64_t step);
		std::unique_ptr<Iterator> array(Value array);
		std::unique_ptr<Iterator> string(Value string);
		std::unique_ptr<Iterator> combined(std::vector<Value> refs, Heap & heap);
		std::unique_ptr<Iterator> reversed(Value ref);

		Value wrap(const Value & ref, Heap & heap);
		Value next(const Value & ref);
		Value get(const Value & ref);
		void move(const Value & ref, const Value & amount);
		std::uint64_t size(const Value & ref);
	}
}