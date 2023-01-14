#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		std::int64_t size(const Value & ref, Heap & heap) {
			if (is_array(ref)) {
				const auto & arr = heap.read<Array>(ref.u);
				return static_cast<std::int64_t>(arr.size());
			}

			if (is_tuple(ref)) {
				const auto & arr = heap.read<Array>(ref.u);
				return static_cast<std::int64_t>(arr.size());
			}

			if(is_string(ref)) {
				const auto & str = heap.read<String>(ref.u);
				return static_cast<std::int64_t>(str.size());
			}

			if(is_queue(ref) || is_stack(ref)) {
				const auto & deq = heap.read<Deque>(ref.u);
				return static_cast<std::int64_t>(deq.size());
			}

			if(is_map(ref)) {
				const auto & map = heap.read<Map>(ref.u);
				return static_cast<std::int64_t>(map.size());
			}

			throw except::invalid_argument();
		}
	}



	void size(VmCore & core) {
		const auto ref = core.stack.pop();
		core.stack.push(size(ref, core.heap));
	}



	void empty(VmCore & core) {
		const auto ref = core.stack.pop();
		core.stack.push(size(ref, core.heap) == 0);
	}
}