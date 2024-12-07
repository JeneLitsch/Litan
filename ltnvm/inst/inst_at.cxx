#include "instructions.hxx"
#include "ltnvm/utils/index.hxx"

namespace ltn::vm::inst {
	void at(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_array(ref) || is_tuple(ref)) {
			const auto & arr = *value::as<Contiguous>(ref);
			const auto index = to_index(key, std::size(arr));
			core.stack.push(arr[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = *value::as<String>(ref);
			const auto index = to_index(key, std::size(str));
			const auto chr = str[static_cast<std::size_t>(index)];
			core.stack.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = *value::as<Map>(ref);
			if(map.contains(key)) {
				core.stack.push(map.at(key));
			}
			else {
				core.stack.push(value::null);
			}
			return;
		}

		throw except::invalid_argument();
	}
}