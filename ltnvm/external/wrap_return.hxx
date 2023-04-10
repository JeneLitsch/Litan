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

	inline Value wrap_return(std::string value, Heap & heap) {
		auto ptr = heap.alloc<String>(std::move(value));
		return value::string(ptr);
	}
	
	template <typename T>
	inline Value wrap_return(const std::vector<T> & vector, Heap & heap) {
		auto ptr = heap.alloc<Array>({});
		auto & array = heap.read<Array>(ptr);
		for(const T & elem : vector) {
			array.push_back(wrap_return(elem, heap));
		} 
		return value::array(ptr);
	}
}