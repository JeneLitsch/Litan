#pragma once
#include "Contiguous.hxx"

namespace ltn::vm {
	struct Array : Contiguous {
		Array() 
			: Contiguous{} {};

		Array(std::vector<Value> && values) 
			: Contiguous{std::move(values)} {};
	};

	inline Array clone(const Array & arr) {
		return arr;
	}
}