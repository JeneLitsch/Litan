#include "instructions.hxx"
#include "ltnvm/index.hxx"

namespace ltn::vm::inst {
	void at(VmCore & core) {
		const auto key = core.reg.pop();
		const auto ref = core.reg.pop();
		
		if(is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u).get();
			const auto index = to_index(key);
			guard_index(arr, index);
			core.reg.push(arr[static_cast<std::size_t>(index)]);
			return;
		}

		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			const auto & array = core.heap.read<Array>(range.array).get();
			const auto index = to_index(key);
			if(index < 0 || index >= range.end - range.begin) {
				throw except::out_of_range();
			} 
			core.reg.push(array[static_cast<std::size_t>(range.begin + index)]);
			return;
		}

		if(is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u).get();
			const auto index = to_index(key);
			guard_index(str, index);
			const auto chr = str[static_cast<std::size_t>(index)];
			core.reg.push(value::character(chr));
			return;
		}

		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref.u).get();
			if(map.contains(key)) {
				core.reg.push(map.at(key));
			}
			else {
				core.reg.push(value::null);
			}
			return;
		}

		throw except::invalid_argument();
	}
}