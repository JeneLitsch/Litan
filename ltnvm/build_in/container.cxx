#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/native/native.hxx"
#include "ltnvm/stdlib/array.hxx"
#include "ltnvm/stdlib/tuple.hxx"
#include "ltnvm/stdlib/map.hxx"
#include "ltnvm/stdlib/string.hxx"
#include "ltnvm/stdlib/stack.hxx"
#include "ltnvm/stdlib/queue.hxx"

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
			Map * map = value::as<Map>(ref);
			return value::boolean(map->contains(key));
		}

		throw except::invalid_argument();
	}



	Value size(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref)) return call<stdlib::array_size>(core, { ref });
		if(is_tuple(ref)) return call<stdlib::tuple_size>(core, { ref });
		if(is_string(ref)) return call<stdlib::string_size>(core, { ref });
		if(is_queue(ref)) return call<stdlib::queue_size>(core, { ref });
		if(is_stack(ref)) return call<stdlib::stack_size>(core, { ref });
		if(is_map(ref)) return call<stdlib::map_size>(core, { ref });
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
			const Array * arr = value::as<Array>(ref);
			if(std::empty(*arr)) throw except::out_of_range();
			return arr->unsafe_front();
		}

		if (is_string(ref)) {
			const String * str = value::as<String>(ref);
			if(std::empty(*str)) throw except::out_of_range();
			return value::character(str->unsafe_front());
		}

		throw except::invalid_argument();
	}
	
	Value back(VMCore & core) {
		const auto ref = core.stack.pop();
		
		if (is_array(ref)) {
			const Array * arr = value::as<Array>(ref);
			if(std::empty(*arr)) throw except::out_of_range();
			return arr->unsafe_back();
		}

		if (is_string(ref)) {
			const String * str = value::as<String>(ref);
			if(std::empty(*str)) throw except::out_of_range();
			return value::character(str->unsafe_back());
		}

		throw except::invalid_argument();
	}
}