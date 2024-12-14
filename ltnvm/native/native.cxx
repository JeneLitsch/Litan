#include "native.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/objects/objects.hxx"

namespace ltn::vm {
	Value search_native_function_table(NativeFunctionTable & table, std::uint64_t id) {
		if (table.contains(id)) {
			return value::native_function(&table.at(id));
		}
		else {
			return value::null;
		}
	}


	
	Array * req_array(const Value * value) {
		if (is_array(*value)) {
			return value::as<Array>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}



	Tuple * req_tuple(const Value * value) {
		if (is_tuple(*value)) {
			return value::as<Tuple>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}



	Map * req_map(const Value * value) {
		if (is_map(*value)) {
			return value::as<Map>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}



	String * req_string(const Value * value) {
		if (is_string(*value)) {
			return value::as<String>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}




	FunctionPointer * req_function_pointer(const Value * value) {
		if (is_fxptr(*value)) {
			return value::as<FunctionPointer>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}


	std::int64_t req_int(const Value * value) {
		if (is_int(*value)) {
			return value->i;
		}
		else {
			throw except::invalid_argument();
		}
	}
}