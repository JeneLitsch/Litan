#include "instructions.hxx"
#include <stdexcept>
#include "ltnvm/convert.hxx"
#include "ltnvm/index.hxx"
namespace ltn::vm::inst {
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
			if(std::empty(arr)) throw except::out_of_range();
			core.stack.push(arr.front());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			if(std::empty(str)) throw except::out_of_range();
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
			if(std::empty(arr)) throw except::out_of_range();
			core.stack.push(arr.back());
			return;
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			if(std::empty(str)) throw except::out_of_range();
			const auto chr = str.back(); 
			core.stack.push(value::character(chr));
			return;
		}

		throw except::invalid_argument();
	}	
}