#include "instructions.hxx"
#include <stdexcept>
#include "ltnvm/convert.hxx"
#include "ltnvm/index.hxx"
namespace ltn::vm::inst {
	
	void push(VmCore & core) {
		const auto elem = core.reg.pop();
		const auto ref = core.reg.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			container.push_back(elem);
			return;
		}
		
		throw except::invalid_argument();
	}


	void pop(VmCore & core) {
		const auto ref = core.reg.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			core.reg.push(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			container.pop_back();
			core.reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			container.pop_front();
			core.reg.push(elem);
			return;
		}
	
		throw except::invalid_argument();
	}


	void peek(VmCore & core) {
		const auto ref = core.reg.pop();

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			const auto elem = container.back();
			core.reg.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u).get();
			const auto elem = container.front();
			core.reg.push(elem);
			return;
		}

		throw except::invalid_argument();
	}


	void contains(VmCore & core) {
		const auto key = core.reg.pop();
		const auto ref = core.reg.pop();

		if(is_map(ref)) {
			auto & container = core.heap.read<Map>(ref.u).get();
			core.reg.push(container.contains(key));
			return;
		}

		throw except::invalid_argument();
	}


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

		if(is_fxptr(ref)) {
			const auto & fxptr = core.heap.read<FxPointer>(ref.u);
			core.reg.push(static_cast<std::int64_t>(fxptr.params));
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


	void front(VmCore & core) {
		const auto ref = core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u).get();
			core.reg.push(arr.front());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u).get();
			const auto chr = str.front(); 
			core.reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}

	
	void back(VmCore & core) {
		const auto ref = core.reg.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u).get();
			core.reg.push(arr.back());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u).get();
			const auto chr = str.back(); 
			core.reg.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}	
}