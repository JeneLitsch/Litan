#pragma once
#include "litan_core/reserved_members.hxx"
#include "litan_vm/VMCore.hxx"
#include "litan_vm/Exception.hxx"

namespace ltn::vm {
	inline void load_onto_stack(VMStack & stack, const auto & values) {
		for(const auto c : values) {
			stack.push(c);
		}
	}

	// Function is executed completely during current instruction
	Value invoke_script_function_immediatly(VMCore & core, const ScriptFunctionPointer & function, const Value * args, std::uint64_t arity);
	Value invoke_native_function_immediatly(VMCore & core, const NativeFunctionPointer & function, const Value * args, std::uint64_t arity);
	Value invoke_function_immediatly(VMCore & core, const Value & ref, const Value * args, std::uint64_t arity);

	// Function is executed after current instruction
	void invoke_native_function(VMCore & core, const Value ref_fx, std::uint64_t arity);
	void invoke_script_function(VMCore & core, const Value ref_fx, std::uint64_t arity);
	void invoke_coroutine(VMCore & core, const Value ref_fx, std::uint64_t arity);
	void invoke_function(VMCore & core, const Value ref_fx, std::uint64_t arity);
}