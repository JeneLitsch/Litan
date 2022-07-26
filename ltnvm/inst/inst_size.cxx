#include "instructions.hxx"

namespace ltn::vm::inst {
	void size(VmCore & core) {
		const auto ref = core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			core.reg.push(static_cast<std::int64_t>(arr.arr.size()));
			return;
		}

		if(is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			core.reg.push(static_cast<std::int64_t>(str.str.size()));
			return;
		}


		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			core.reg.push(range.end - range.begin);
			return;
		}

		if(is_queue(ref) || is_stack(ref)) {
			const auto & deq = core.heap.read<Deque>(ref.u).get();
			core.reg.push(static_cast<std::int64_t>(deq.size()));
			return;
		}

		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref.u).get();
			core.reg.push(static_cast<std::int64_t>(map.size()));
			return;
		}

		throw except::invalid_argument();
	}
}