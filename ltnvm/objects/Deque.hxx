#pragma once
#include <deque>
#include <string_view>
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	// Implements stack, queue, ...
	using Deque = std::deque<Value>;

	inline Deque clone(const Deque & deq) {
		return deq;
	}
}