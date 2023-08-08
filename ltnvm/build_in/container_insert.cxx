#include "algorithm.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/index.hxx"
#include "ltnvm/inst/instructions.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm::build_in {
	Value insert_front(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_string(ref)) {
			auto & str = core.heap.read<String>(ref);
			const auto strL = stringify(elem, core);
			str.replace_underlying(strL + str.get_underlying());
			return value::null;
		}

		if(is_array(ref)) {
			auto & arr = core.heap.read<Array>(ref);
			arr.insert(arr.begin(), elem);
			return value::null;
		} 

		throw except::invalid_argument();
	}



	Value insert_back_string(VmCore & core, Value ref, Value elem) {
		auto * str = ref.as<String>();
		
		if(is_char(elem)) {
			str->push_back(elem.c);
		}
		else if(is_string(elem)) {
			str->append(elem.as<String>()->get_underlying());
		}
		else {
			str->append(stringify(elem, core));
		}
		
		return value::null;
	}



	Value insert_back(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_string(ref)) {
			return insert_back_string(core, ref, elem);
		}

		if(is_array(ref)) {
			auto & arr = core.heap.read<Array>(ref);
			arr.push_back(elem);
			return value::null;
		} 
		
		throw except::invalid_argument();
	}



	namespace {
		auto to_iter(auto & container, const Value & key) {
			const auto i = to_index(key, std::size(container) + 1);
			return std::begin(container) + i;
		}
	}



	Value insert(VmCore & core) {
		const auto elem = core.stack.pop();
		const auto key = core.stack.pop();
		const auto ref = core.stack.pop();

		if(is_map(ref)) {
			auto & map = core.heap.read<Map>(ref);
			map[key] = elem;
			return value::null;
		}
		
		if(is_string(ref)) {
			auto & str = core.heap.read<String>(ref); 
			const auto strX = stringify(elem, core);
			const auto begin = std::begin(strX);
			const auto end = std::end(strX);
			const auto at = to_iter(str, key);
			str.insert(at, begin, end);
			return value::null;
		}

		if(is_array(ref)) {
			auto & arr = core.heap.read<Array>(ref); 
			const auto at = to_iter(arr, key);
			arr.insert(at, elem);
			return value::null;
		}

		throw except::invalid_argument();
	}
}