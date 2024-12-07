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

		if(is_string(ref)) {
			String * str = value::as<String>(ref);
			const auto strL = stringify(elem, core);
			str->replace_underlying(strL + str->get_underlying());
			return value::null;
		}

		if(is_array(ref)) {
			Array * arr = value::as<Array>(ref);
			arr->insert(std::begin(*arr), elem);
			return value::null;
		} 

		throw except::invalid_argument();
	}



	Value insert_back_string(VMCore & core, Value ref, Value elem) {
		auto * str = value::as<String>(ref);
		
		if(is_char(elem)) {
			str->push_back(elem.c);
		}
		else if(is_string(elem)) {
			str->append(value::as<String>(elem)->get_underlying());
		}
		else {
			str->append(stringify(elem, core));
		}
		
		return value::null;
	}



	Value insert_back(VMCore & core) {
		const auto elem = core.stack.pop();
		const auto ref = core.stack.pop();
		
		if(is_string(ref)) {
			return insert_back_string(core, ref, elem);
		}

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
		
		if(is_string(ref)) {
			String * str = value::as<String>(ref); 
			const auto strX = stringify(elem, core);
			const auto begin = std::begin(strX);
			const auto end = std::end(strX);
			const auto at = to_iter(str, key);
			str->insert(at, begin, end);
			return value::null;
		}

		if(is_array(ref)) {
			Array * arr = value::as<Array>(ref); 
			const auto at = to_iter(arr, key);
			arr->insert(at, elem);
			return value::null;
		}

		throw except::invalid_argument();
	}
}