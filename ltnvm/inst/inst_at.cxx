#include "instructions.hxx"
#include "ltnvm/utils/index.hxx"

namespace ltn::vm::inst {
	void at(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_array(ref) || is_tuple(ref)) {
			const auto & arr = core.heap.read<Array>(ref);
			const auto index = to_index(key, std::size(arr.data));
			core.stack.push(arr.data[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = core.heap.read<String>(ref);
			const auto index = to_index(key, std::size(str.data));
			const auto chr = str.data[static_cast<std::size_t>(index)];
			core.stack.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref);
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