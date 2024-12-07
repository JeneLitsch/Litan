#include "native.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/objects/objects.hxx"

namespace ltn::vm {
	std::pair<std::uint64_t, NativeFunctionPointer> wrap(MemberCode code, NativeFunctionHandle handle, std::uint64_t arity) {
		return std::pair<std::uint64_t, NativeFunctionPointer>{ static_cast<std::uint64_t>(code), NativeFunctionPointer{handle, arity, false} };
	}



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
			return value->as<Array>();
		}
		else {
			throw except::invalid_argument();
		}
	}



	Tuple * req_tuple(const Value * value) {
		if (is_tuple(*value)) {
			return value->as<Tuple>();
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