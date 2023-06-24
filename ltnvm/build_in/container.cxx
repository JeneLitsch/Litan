#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	template<auto INST>
	auto run_inst(VmCore & core) {
		INST(core);
		return core.stack.pop();
	}
	


	Value contains(VmCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) {
			auto & container = core.heap.read<Map>(ref.u);
			return value::boolean(container.contains(key));
		}

		throw except::invalid_argument();
	}



	namespace {
		template<typename Container>
		Value size(const Value & ref, VmCore & core) {
			const auto & container = core.heap.read<Container>(ref.u);
			return value::integer(static_cast<std::int64_t>(std::size(container.data)));
		}
	}



	Value size(VmCore & core) {
		const auto ref = core.stack.pop();
		if (is_array(ref)) return size<Array>(ref, core);
		if (is_tuple(ref)) return size<Array>(ref, core);
		if(is_string(ref)) return size<String>(ref, core);
		if(is_queue(ref)) return size<Deque>(ref, core);
		if(is_stack(ref)) return size<Deque>(ref, core);
		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref.u);
			return value::integer(static_cast<std::int64_t>(std::size(map)));
		}
		if(is_iterator(ref)) return value::integer(iterator::size(ref, core.heap));
		throw except::invalid_argument();
	}
	


	Value empty(VmCore & core) {
		return value::boolean(size(core).i == 0);
	}
	


	Value at(VmCore & core) {
		return run_inst<inst::at>(core);
	}
	

	
	Value front(VmCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			if(std::empty(arr)) throw except::out_of_range();
			return arr.data.front();
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			if(std::empty(str.data)) throw except::out_of_range();
			return value::character(str.data.front());
		}

		throw except::invalid_argument();
	}
	
	Value back(VmCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref.u);
			if(std::empty(arr)) throw except::out_of_range();
			return arr.data.back();
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref.u);
			if(std::empty(str.data)) throw except::out_of_range();
			return value::character(str.data.back());
		}

		throw except::invalid_argument();
	}
}