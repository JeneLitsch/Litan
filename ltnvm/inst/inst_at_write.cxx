#include "instructions.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/utils/convert.hxx"

namespace ltn::vm::inst {
	void at_write(VMCore & core) {
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();
		const auto elem = core.stack.pop();
		
		if(is_array(ref) || is_tuple(ref)) {
			auto & arr = *value::as<Contiguous>(ref);
			const auto index = to_index(key, std::ssize(arr));
			arr.unsafe_at(index) = elem;
			return;
		}

		if(is_map(ref)) {
			auto & map = *value::as<Map>(ref);
			map[key] = elem;
			return;
		}

		throw except::invalid_argument();
	}
}