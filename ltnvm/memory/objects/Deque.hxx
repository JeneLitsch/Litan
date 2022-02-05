#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	// Implements stack, queue, ...
	struct Deque {
		std::deque<Value> deq;
		constexpr static std::string_view typeName = "Queue";
		const auto & get() const {
			return this->deq;
		}
		auto & get() {
			return this->deq;
		}
	};
}