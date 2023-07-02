#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	// Implements stack, queue, ...
	struct Deque : public Object {
		std::deque<Value> data;
	};

	inline Deque clone(const Deque & deq) {
		return deq;
	}
}