#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	// Implements stack, queue, ...
	struct Deque {
		std::deque<Value> data;
	};

	inline Deque clone(const Deque & deq) {
		return deq;
	}
}