#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	Value insert_front(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			Array * arr = value::as<Array>(ref);
			arr->unsafe_insert(std::begin(*arr), elem);
			return value::null;
		} 

		throw except::invalid_argument();
	}




	Value insert_back(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			Array * arr = value::as<Array>(ref);
			arr->push_back(elem);
			return value::null;
		} 
		
		throw except::invalid_argument();
	}



	namespace {
		template<typename Container>
		auto to_iter(Container * container, const Value & key) {
			const auto i = to_index(key, std::size(*container) + 1);
			return std::begin(*container) + i;
		}
	}



	Value insert(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) {
			Map * map = value::as<Map>(ref);
			(*map)[key] = elem;
			return value::null;
		}
		

		if(is_array(ref)) {
			Array * arr = value::as<Array>(ref); 
			const auto at = to_iter(arr, key);
			arr->unsafe_insert(at, elem);
			return value::null;
		}

		throw except::invalid_argument();
	}
}