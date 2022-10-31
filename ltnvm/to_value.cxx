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
			const auto addr = heap.alloc<String>(String{variant.as_string()});
			return value::string(addr);
		}

		if(variant.is_array()) {
			const auto addr = heap.alloc<Array>(Array{});
			auto & array = heap.read<Array>(addr).get();
			for(const auto & elem : variant.as_array()) {
				array.push_back(to_value(elem, heap));
			}
			return value::string(addr);
		}

		return value::null;
	}
}