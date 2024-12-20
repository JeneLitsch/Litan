#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/array.hxx"
#include "ltnvm/stdlib/map.hxx"

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

		if(is_array(ref)) return call<stdlib::array_push>(core, {ref,elem});
		
		throw except::invalid_argument();
	}



	namespace {
		template<typename Container>
		auto to_iter(Container * container, const Value & key) {
			const auto i = to_index(key, std::ssize(*container) + 1);
			return std::begin(*container) + i;
		}
	}



	Value insert(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) return call<stdlib::map_insert>(core, { ref, key, elem });
		if(is_array(ref)) return call<stdlib::array_insert>(core, { ref, key, elem });

		throw except::invalid_argument();
	}
}