#include "instructions.hxx"
#include "ltnvm/index.hxx"

namespace ltn::vm::inst {
	void at(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			const auto index = to_index(key);
			guard_index(arr, index);
			core.stack.push(arr[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_tuple(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			const auto index = to_index(key);
			guard_index(arr, index);
			core.stack.push(arr[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			const auto index = to_index(key);
			guard_index(str, index);
			const auto chr = str[static_cast<std::size_t>(index)];
			core.stack.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref.u);
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