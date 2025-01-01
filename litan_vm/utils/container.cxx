#include "container.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/utils/index.hxx"

namespace ltn::vm {
	Value get_element_from_container(Value container, Value key) {
		if(is_array(container) || is_tuple(container)) {
			const auto & arr = *value::as<Contiguous>(container);
			const auto index = to_index(key, std::ssize(arr));
			return arr.unsafe_at(index);
		}

		if(is_string(container)) {
			const auto & str = *value::as<String>(container);
			const auto index = to_index(key, std::ssize(str));
			const auto chr = str.at(index);
			return value::integer(chr);
		}

		if(is_map(container)) {
			const auto & map = *value::as<Map>(container);
			if(map.contains(key)) {
				return map.at(key);
			}
			else {
				return value::null;
			}
		}
	
		throw except::invalid_argument();
	}
}