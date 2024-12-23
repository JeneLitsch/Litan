#include "instructions.hxx"
#include "ltnvm/utils/index.hxx"

namespace ltn::vm::inst {
	void at(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_array(ref) || is_tuple(ref)) {
			const auto & arr = *value::as<Contiguous>(ref);
			const auto index = to_index(key, std::ssize(arr));
			core.stack.push(arr.unsafe_at(index));
			return;
		}

		if(is_string(ref)) {
			const auto & str = *value::as<String>(ref);
			const auto index = to_index(key, std::ssize(str));
			const auto chr = str.at(index);
			core.stack.push(value::integer(chr));
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