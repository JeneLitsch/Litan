#include "json.hxx"
#include <sstream>
#include <istream>
#include "stdxx/json.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/json.hxx"

namespace ltn::vm::build_in::json {
	Value parse(VMCore & core) {
		try {
			auto str = core.stack.pop();
			if(!is_string(str)) {
				throw except::invalid_argument();
			}

			std::istringstream iss {value::as<String>(str)->get_underlying()};
			stx::json::node json_node;
			iss >> json_node;
			return json_to_value(json_node, core);
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}



	Value print(VMCore & core) {
		try {
			std::ostringstream oss;
			const stx::json::node json = value_to_json(core.stack.pop()); 
			oss << json;
			return value::string(core.heap.make<String>(oss.str()));
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}
}