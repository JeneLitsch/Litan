#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	// Implements stack, queue, ...
	struct Deque {
		std::deque<Value> deq;
		bool marked = false;
		bool in_use = false;
	};

	inline Deque clone(const Deque & deq) {
		return deq;
	}
}