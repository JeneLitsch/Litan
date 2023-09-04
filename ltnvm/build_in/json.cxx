#include "json.hxx"
#include <sstream>
#include <istream>
#include "stdxx/json.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::build_in::json {
	namespace {
		Value json_to_ltn(const stx::json::node & json, VMCore & core);

		Value json_to_ltn_impl(std::monostate, VMCore & core) {
			return value::null;
		}

		Value json_to_ltn_impl(bool x, VMCore & core) {
			return value::boolean(x);
		}

		Value json_to_ltn_impl(double x, VMCore & core) {
			return value::floating(x);
		}
		
		Value json_to_ltn_impl(const std::string & x, VMCore & core) {
			return value::string(core.heap.make<String>(x));
		}

		Value json_to_ltn_impl(const std::vector<stx::json::node> & x, VMCore & core) {
			auto * arr = core.heap.make<Array>();
			for(const auto & elem : x) {
				arr->push_back(json_to_ltn(elem, core));
			}
			return value::array(arr);
		}

		Value json_to_ltn_impl(const std::vector<std::pair<std::string, stx::json::node>> & x, VMCore & core) {
			auto * map = core.heap.make<Map>(&core);
			for(const auto & [key, val] : x) {
				auto str = value::string(core.heap.make<String>(key)); 
				(*map)[str] = json_to_ltn(val, core);
			}
			return value::map(map);
		}

		Value json_to_ltn(const stx::json::node & json, VMCore & core) {
			return std::visit([&] (auto & x) {
				return json_to_ltn_impl(x, core);
			}, json.data);
		}
	}



	Value parse(VMCore & core) {
		try {
			auto str = core.stack.pop();
			if(!is_string(str)) {
				throw except::invalid_argument();
			}

			std::istringstream iss {str.as<String>()->get_underlying()};
			stx::json::node json_node;
			iss >> json_node;
			return json_to_ltn(json_node, core);
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}



	namespace {
		stx::json::node ltn_to_json(const Value & value) {
			if(is_null(value))  return nullptr;
			if(is_bool(value))  return value.b;
			if(is_char(value))  return value.c;
			if(is_int(value))   return value.i;
			if(is_float(value)) return value.f;
			if(is_string(value)) {
				return value.as<String>()->get_underlying();
			}
			if(is_array(value)) {
				stx::json::node node;
				stx::json::write_iterator it 
					= stx::json::write_iterator{node}
					= stx::json::array;
				for(const auto & elem : *value.as<Array>()) {
					it.push_back(ltn_to_json(elem));
				}
				return node;
			}
			if(is_map(value)) {
				stx::json::node node;
				stx::json::write_iterator it 
					= stx::json::write_iterator{node}
					= stx::json::object;
				for(const auto & [key, val] : *value.as<Map>()) {
					if(!is_string(key)) {
						throw except::invalid_argument();
					}
					it[key.as<String>()->get_underlying()] = ltn_to_json(val);
				}
				return node;
			}

			throw except::invalid_argument();
		}
	}



	Value print(VMCore & core) {
		try {
			std::ostringstream oss;
			const stx::json::node json = ltn_to_json(core.stack.pop()); 
			oss << json;
			return value::string(core.heap.make<String>(oss.str()));
		}
		catch(...) {
			throw except::invalid_argument();
		}
	}
}