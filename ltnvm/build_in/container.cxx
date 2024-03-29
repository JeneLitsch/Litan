#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	template<auto INST>
	auto run_inst(VMCore & core) {
		INST(core);
		return core.stack.pop();
	}
	


	Value contains(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) {
			auto & container = core.heap.read<Map>(ref);
			return value::boolean(container.contains(key));
		}

		throw except::invalid_argument();
	}



	namespace {
		template<typename Container>
		Value size(const Value & ref, VMCore & core) {
			const auto & container = core.heap.read<Container>(ref);
			return value::integer(static_cast<std::int64_t>(std::size(container)));
		}
	}



	Value size(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref)) return size<Array>(ref, core);
		if(is_tuple(ref)) return size<Tuple>(ref, core);
		if(is_string(ref)) return size<String>(ref, core);
		if(is_queue(ref)) return size<Segmented>(ref, core);
		if(is_stack(ref)) return size<Segmented>(ref, core);
		if(is_map(ref)) {
			const auto & map = core.heap.read<Map>(ref);
			return value::integer(static_cast<std::int64_t>(std::size(map)));
		}
		if(is_iterator(ref)) return value::integer(iterator::size(ref));
		throw except::invalid_argument();
	}
	


	Value empty(VMCore & core) {
		return value::boolean(size(core).i == 0);
	}
	


	Value at(VMCore & core) {
		return run_inst<inst::at>(core);
	}
	

	
	Value front(VMCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref);
			if(std::empty(arr)) throw except::out_of_range();
			return arr.front();
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref);
			if(std::empty(str)) throw except::out_of_range();
			return value::character(str.front());
		}

		throw except::invalid_argument();
	}
	
	Value back(VMCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const auto & arr = core.heap.read<Array>(ref);
			if(std::empty(arr)) throw except::out_of_range();
			return arr.back();
		}

		if (is_string(ref)) {
			const auto & str = core.heap.read<String>(ref);
			if(std::empty(str)) throw except::out_of_range();
			return value::character(str.back());
		}

		throw except::invalid_argument();
	}
}