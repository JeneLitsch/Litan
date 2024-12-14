#pragma once
#include <map>
#include "ltnvm/objects/NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"

namespace ltn::vm {
	struct Array;
	struct Tuple;
	struct Map;
	struct String;
	struct Queue;
	struct Stack;
	using NativeFunctionTable = std::map<std::uint64_t, NativeFunctionPointer>;

	template<typename FuncHeader>
	std::pair<std::uint64_t, NativeFunctionPointer> wrap(MemberCode code) {
		return std::pair<std::uint64_t, NativeFunctionPointer>{
			static_cast<std::uint64_t>(code),
			NativeFunctionPointer{
				nullptr,
				FuncHeader::func,
				FuncHeader::arity,
				false
			}
		};
	}

	template<typename FuncHeader>
	Value call(VMCore & core, const std::array<Value, FuncHeader::arity> args) {
		ltn_Context context {
			.core = &core,
		};
		return FuncHeader::func(&context, args.data());
	}

	
	Value search_native_function_table(NativeFunctionTable & table, std::uint64_t id);


	
	Array * req_array(const Value * value);
	Tuple * req_tuple(const Value * value);
	Map * req_map(const Value * value);
	String * req_string(const Value * value);
	Queue * req_queue(const Value * value);
	Stack * req_stack(const Value * value);
	FunctionPointer * req_function_pointer(const Value * value);
	std::int64_t req_int(const Value * value);
}