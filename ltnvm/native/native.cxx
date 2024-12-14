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



	template<typename Type, auto is_type>
	Type * req_type(const Value * value) {
		if (is_type(*value)) {
			return value::as<Type>(*value);
		}
		else {
			throw except::invalid_argument();
		}
	}


	
	Array * req_array(const Value * value) {
		return req_type<Array, is_array>(value);
	}



	Tuple * req_tuple(const Value * value) {
		return req_type<Tuple, is_tuple>(value);
	}



	Map * req_map(const Value * value) {
		return req_type<Map, is_map>(value);
	}



	String * req_string(const Value * value) {
		return req_type<String, is_string>(value);
	}



	Queue * req_queue(const Value * value) {
		return req_type<Queue, is_queue>(value);
	}



	Stack * req_stack(const Value * value) {
		return req_type<Stack, is_stack>(value);
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