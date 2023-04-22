#include "ltnvm/to_variant.hxx"
#include "ltnvm/type_check.hxx"

namespace ltn::vm {
	Variant to_variant(const Value & value, Heap & heap) {
		if(is_null(value)) {
			return Variant{};
		}

		if(is_bool(value)) {
			return Variant{value.b};
		}
		
		if(is_char(value)) {
			return Variant{value.c};
		}

		if(is_int(value)) {
			return Variant{value.i};
		}

		if(is_float(value)) {
			return Variant{value.f};
		}

		if(is_string(value)) {
			return Variant{heap.read<String>(value).str};
		}

		if(is_array(value)) {
			auto & array = heap.read<Array>(value);
			std::vector<Variant> vector;
			for(const auto & elem : array.arr) {
				vector.push_back(to_variant(elem, heap));
			}
			return Variant{vector};
		}

		return Variant{};
	}
}