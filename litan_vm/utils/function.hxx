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


	std::vector<Value> read_from_stack(VMStack & stack, std::uint64_t arity);
	void prepare_args(VMCore & core, const Value ref_fx, std::uint64_t arity);



	Value run_core(VMCore & core);


	Value invoke_script_function_recursive(
		VMCore & core,
		const ScriptFunctionPointer & function,
		const auto & ...args) {

		const auto arg_arity = sizeof...(args);
		if(function.arity() != arg_arity) throw except::invalid_parameters(arg_arity, function.arity());
		if(function.is_variadic) throw except::invalid_member_access();
		(core.stack.push(args),...);
		const auto prev = core.pc;
		auto * entry = core.function_pool[function.index];
		core.pc = core.code_begin + entry->address;
		core.stack.push_frame(core.code_end - 1, arg_arity, entry); 
		for(const auto c : function.captured) core.stack.push(c);
		auto result = run_core(core);
		core.pc = prev;
		return result;
	}



	Value invoke_native_function_recursive(VMCore & core, const Value ref_fx, std::uint64_t arity);



	Value invoke_function_recursive(
		VMCore & core,
		const Value & ref,
		const auto & ...args) {

		if (is_script_function(ref)) {
			ScriptFunctionPointer * function = value::as<ScriptFunctionPointer>(ref);
			return invoke_script_function_recursive(core, *function, args...);
		}
		else {
			throw except::invalid_argument();
		}
	}
	




	void invoke_native_function(VMCore & core, const Value ref_fx, std::uint64_t arity);
	void invoke_script_function(VMCore & core, const Value ref_fx, std::uint64_t arity);
	void invoke_coroutine(VMCore & core, const Value ref, std::uint64_t arity);
}