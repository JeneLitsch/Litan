#include "instructions.hxx"
#include <stdexcept>
#include "ltnvm/convert.hxx"
#include "ltnvm/index.hxx"
namespace ltn::vm::inst {
	
	void push(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u);
			container.push_back(elem);
			return;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			container.push_back(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			container.push_back(elem);
			return;
		}
		
		throw except::invalid_argument();
	}



	void pop(VmCore & core) {
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u);
			const auto elem = container.back();
			container.pop_back();
			core.stack.push(elem);
			return;
		}

		if(is_string(ref)) {
			auto & container = core.heap.read<String>(ref.u);
			const auto elem = container.back();
			container.pop_back();
			core.stack.push(value::character(elem));
			return;
		}

		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			const auto elem = container.back();
			container.pop_back();
			core.stack.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			const auto elem = container.front();
			container.pop_front();
			core.stack.push(elem);
			return;
		}
	
		throw except::invalid_argument();
	}



	void peek(VmCore & core) {
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			auto & container = core.heap.read<Array>(ref.u);
			const auto elem = container.back();
			core.stack.push(elem);
			return;
		}

		if(is_string(ref)) {
			auto & container = core.heap.read<String>(ref.u);
			const auto elem = container.back();
			core.stack.push(value::character(elem));
			return;
		}


		if(is_stack(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			const auto elem = container.back();
			core.stack.push(elem);
			return;
		}

		if(is_queue(ref)) {
			auto & container = core.heap.read<Deque>(ref.u);
			const auto elem = container.front();
			core.stack.push(elem);
			return;
		}

		throw except::invalid_argument();
	}



	void contains(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) {
			auto & container = core.heap.read<Map>(ref.u);
			core.stack.push(container.contains(key));
			return;
		}

		throw except::invalid_argument();
	}



	void front(VmCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			core.stack.push(arr.front());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			const auto chr = str.front(); 
			core.stack.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}


	
	void back(VmCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			core.stack.push(arr.back());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			const auto chr = str.back(); 
			core.stack.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}	
}