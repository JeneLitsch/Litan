#pragma once
#include <map>
#include "ltnvm/objects/NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"

namespace ltn::vm {
	struct Array;
	struct Tuple;
	using NativeFunctionTable = std::map<std::uint64_t, NativeFunctionPointer>;
	std::pair<std::uint64_t, NativeFunctionPointer> wrap(MemberCode code, NativeFunctionHandle handle, std::uint64_t arity);
	Value search_native_function_table(NativeFunctionTable & table, std::uint64_t id);
	
	Array * req_array(const Value * value);
	Tuple * req_tuple(const Value * value);
	std::int64_t req_int(const Value * value);
}