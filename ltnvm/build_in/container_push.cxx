#include "container.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	Value push(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_array(ref)) {
			Array * container = value::as<Array>(ref);
			container->push_back(elem);
			return value::null;
		}

		if(is_string(ref)) {
			return insert_back_string(core, ref, elem);
		}

		if(is_queue(ref)) {
			Segmented * container = value::as<Segmented>(ref);
			container->push_back(elem);
			return value::null;
		}
		
		throw except::invalid_argument();
	}
}