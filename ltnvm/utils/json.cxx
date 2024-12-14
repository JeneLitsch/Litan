#include "json.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	namespace {

		Value json_to_value_impl(std::monostate, VMCore &) {
			return value::null;
		}

		Value json_to_value_impl(bool x, VMCore &) {
			return value::boolean(x);
		}

		Value json_to_value_impl(double x, VMCore &) {
			return value::floating(x);
		}
		
		Value json_to_value_impl(const std::string & x, VMCore & core) {
			return value::string(core.heap.make<String>(x));
		}

		Value json_to_value_impl(const std::vector<stx::json::node> & x, VMCore & core) {
			auto * arr = core.heap.make<Array>();
			for(const auto & elem : x) {
				arr->push_back(json_to_value(elem, core));
			}
			return value::array(arr);
		}

		Value json_to_value_impl(const std::vector<std::pair<std::string, stx::json::node>> & x, VMCore & core) {
			auto * map = core.heap.make<Map>(&core);
			for(const auto & [key, val] : x) {
				auto str = value::string(core.heap.make<String>(key)); 
				(*map)[str] = json_to_value(val, core);
			}
			return value::map(map);
		}

	}



	Value json_to_value(const stx::json::node & json, VMCore & core) {
		return std::visit([&] (auto & x) {
			return json_to_value_impl(x, core);
		}, json.data);
	}



	stx::json::node value_to_json(const Value & value) {
		if(is_null(value))  return nullptr;
		if(is_bool(value))  return value.b;
		if(is_char(value))  return value.c;
		if(is_int(value))   return value.i;
		if(is_float(value)) return value.f;
		if(is_string(value)) {
			return value::as<String>(value)->copy_to_std_string();
		}
		if(is_array(value)) {
			stx::json::node node;
			stx::json::write_iterator it 
				= stx::json::write_iterator{node}
				= stx::json::array;
			for(const auto & elem : *value::as<Array>(value)) {
				it.push_back(value_to_json(elem));
			}
			return node;
		}
		if(is_map(value)) {
			stx::json::node node;
			stx::json::write_iterator it 
				= stx::json::write_iterator{node}
				= stx::json::object;
			for(const auto & [key, val] : *value::as<Map>(value)) {
				if(!is_string(key)) {
					throw std::runtime_error{""};
				}
				it[value::as<String>(key)->copy_to_std_string()] = value_to_json(val);
			}
			return node;
		}

		throw std::runtime_error{""};
	}
}