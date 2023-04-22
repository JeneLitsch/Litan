#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct Array {
		std::vector<Value> arr;
		bool marked = false;
		bool in_use = false;

		auto & get() { return arr; }
	};
	
	inline Array clone(const Array & arr) {
		return arr;
	}
}