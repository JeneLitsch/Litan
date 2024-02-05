#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class Heap;
	struct VMCore;

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
		Value wrap(const Value & ref, VMCore & core);
		Value next(const Value & ref);
		Value get(const Value & ref);
		void move(const Value & ref, const Value & amount);
		std::uint64_t size(const Value & ref);
	}
}