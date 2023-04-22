#include "to_value.hxx"

namespace ltn::vm {
	Value to_value(const Variant & variant, Heap & heap) {
		if(variant.is_null()) {
			return value::null;
		}

		if(variant.is_bool()) {
			return value::boolean(variant.as_bool());
		}

		if(variant.is_char()) {
			return value::character(variant.as_char());
		}

		if(variant.is_int()) {
			return value::integer(variant.as_int());
		}

		if(variant.is_float()) {
			return value::floating(variant.as_float());
		}

		if(variant.is_string()) {
			auto * ptr = heap.alloc(String{variant.as_string()});
			return value::string(ptr);
		}

		if(variant.is_array()) {
			auto * arr = heap.alloc<Array>({});
			for(const auto & elem : variant.as_array()) {
				arr->arr.push_back(to_value(elem, heap));
			}
			return value::array(arr);
		}

		return value::null;
	}
}