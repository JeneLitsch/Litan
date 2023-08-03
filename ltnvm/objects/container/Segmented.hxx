#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	// Implements stack, queue, ...
	struct Segmented : public Object {
		std::deque<Value> data;
	};

	inline Segmented clone(const Segmented & deq) {
		return deq;
	}
}