#include "native.hxx"
#include "ltnvm/objects/container/Array.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	std::pair<std::uint64_t, NativeFunctionPointer> wrap(MemberCode code, NativeFunctionHandle handle, std::uint64_t arity) {
		return std::pair<std::uint64_t, NativeFunctionPointer>{ static_cast<std::uint64_t>(code), NativeFunctionPointer{handle, arity, false} };
	}


	
	Array * req_array(const Value * value) {
		if (is_array(*value)) {
			return value->as<Array>();
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