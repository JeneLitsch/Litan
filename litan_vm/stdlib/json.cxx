#include "json.hxx"
#include "litan_vm/utils/json.hxx"
#include "stdxx/json.hxx"


namespace ltn::vm::stdlib {
	Value json_print::func(Context * context, const Value * args) {
		try {
			std::ostringstream oss;
			const stx::json::node json = value_to_json(args[0]); 
			oss << json;
			VMCore * core = static_cast<VMCore *>(context->core);
			return value::string(core->heap.make<String>(oss.str()));
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}


	
	Value json_parse::func(Context * context, const Value * args) {
		try {
			if(!is_string(args[0])) {
				throw except::invalid_argument();
			}

			std::istringstream iss { value::as<String>(args[0])->copy_to_std_string() };
			stx::json::node json_node;
			iss >> json_node;
			VMCore * core = static_cast<VMCore *>(context->core);
			return json_to_value(json_node, *core);
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}
}