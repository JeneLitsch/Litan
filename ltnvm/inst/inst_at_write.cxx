#include "instructions.hxx"
#include "ltnvm/index.hxx"
#include "ltnvm/convert.hxx"

namespace ltn::vm::inst {
	void at_write(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		const auto elem = core.stack.pop();
		
		if(is_array(ref) || is_tuple(ref)) {
			auto & arr = core.heap.read<Array>(ref).get();
			const auto index = to_index(key);
			guard_index(arr, index);
			arr[static_cast<std::size_t>(index)] = elem;
			return;
		}

		if(is_string(ref)) {
			auto & str = core.heap.read<String>(ref).get();
			const auto index = to_index(key);
			guard_index(str, index);
			str[static_cast<std::size_t>(index)] = convert::to_char(elem);
			return;
		}

		if(is_map(ref)) {
			auto & map = core.heap.read<Map>(ref).map;
			map[key] = elem;
			return;
		}

		throw except::invalid_argument();
	}
}