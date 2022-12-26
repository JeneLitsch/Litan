#pragma once
#include "ltnvm/memory/Heap.hxx"
#include "ltnvm/memory/Value.hxx"

namespace ltn::vm::ext {
	inline Value wrap_return(bool value, Heap &) {
		return value::boolean(value);
	}
		
	inline Value wrap_return(std::integral auto value, Heap &) {
		return value::integer(value);
	}
		
	inline Value wrap_return(std::floating_point auto value, Heap &) {
		return value::floating(value);
	}

	inline Value wrap_return(const std::string & value, Heap & heap) {
		auto ptr = heap.alloc<String>({value});
		return value::string(ptr);
	}
}