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