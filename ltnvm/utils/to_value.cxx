#include "to_value.hxx"

namespace ltn::vm {
	Value to_value(const Any & any, Heap & heap) {
		if(any.is_null()) {
			return value::null;
		}

		if(any.is_bool()) {
			return value::boolean(any.as_bool());
		}

		if(any.is_char()) {
			return value::character(any.as_char());
		}

		if(any.is_int()) {
			return value::integer(any.as_int());
		}

		if(any.is_float()) {
			return value::floating(any.as_float());
		}

		if(any.is_string()) {
			const auto address = heap.alloc(String{any.as_string()});
			return value::string(address);
		}

		if(any.is_array()) {
			const auto address = value::array(heap.alloc<Array>({}));
			auto & array = heap.read<Array>(address);
			for(const auto & elem : any.as_array()) {
				array.push_back(to_value(elem, heap));
			}
			return address;
		}

		return value::null;
	}
}