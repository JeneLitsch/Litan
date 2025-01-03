#pragma once
#include <map>
#include "litan_vm/objects/NativeFunctionPointer.hxx"
#include "litan_core/reserved_members.hxx"
#include "litan_vm/VMCore.hxx"

namespace ltn::vm {
	struct Array;
	struct Tuple;
	class Map;
	struct String;
	struct Queue;
	struct Stack;
	using NativeFunctionTable = std::map<std::uint64_t, NativeFunctionPointer>;

	template<typename FuncHeader>
	NativeFunctionPointer make_native_function_pointer() {
		return NativeFunctionPointer{
			nullptr,
			FuncHeader::func,
			FuncHeader::arity,
			false
		};
	}

	template<typename FuncHeader>
	std::pair<std::uint64_t, NativeFunctionPointer> wrap(ReservedMemberCode code) {
		return {
			static_cast<std::uint64_t>(code),
			make_native_function_pointer<FuncHeader>(),
		};
	}

	template<typename FuncHeader>
	Value call(VMCore & core, const std::array<Value, FuncHeader::arity> args) {
		ltn_Context context {
			.core = &core,
		};
		return FuncHeader::func(&context, args.data());
	}



	template<typename FuncHeader>
	Value as_build_in(VMCore & core) {
		return call<FuncHeader>(core, core.stack.pop_n<FuncHeader::arity>());
	}


	std::optional<Value> search_native_function_table(NativeFunctionTable & table, std::uint64_t id);


	
	std::int64_t req_int(const Value * value);

	Array * req_array(const Value * value);
	Tuple * req_tuple(const Value * value);
	Map * req_map(const Value * value);
	String * req_string(const Value * value);
	Queue * req_queue(const Value * value);
	Stack * req_stack(const Value * value);
	FunctionPointer * req_function_pointer(const Value * value);
	RandomEngine * req_rng(const Value * value);
}