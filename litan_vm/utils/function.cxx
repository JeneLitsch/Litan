#include "function.hxx"
#include "GCLock.hxx"

namespace ltn::vm {
	Value run_core(VMCore & core);

	Context wrap_context(VMCore & core) {
		return {
			.core = static_cast<void*>(&core),
		};
	}


	std::vector<Value> read_from_stack(VMStack & stack, std::uint64_t arity) {
		std::vector<Value> args;
		for(std::size_t i = 0; i < arity; ++i) {
			args.push_back(stack.pop());
		}
		std::reverse(std::begin(args), std::end(args));
		return args;
	}



	void prepare_args(VMCore & core, const Value ref_fx, std::uint64_t arity) {
		const auto & fxptr = *value::as<FunctionPointer>(ref_fx);
		if(arity >= fxptr.arity() && fxptr.is_variadic) {
			Tuple tuple {read_from_stack(core.stack, arity - fxptr.arity())};
			core.stack.push(value::tuple(core.heap.alloc(std::move(tuple))));
		}
		else if(arity > fxptr.arity()) {
			throw except::invalid_parameters(fxptr.arity(), arity);
		}
		else if(arity < fxptr.arity()) {
			throw except::invalid_parameters(fxptr.arity(), arity);
		}
	}



	Value invoke_script_function_immediatly(VMCore & core, const ScriptFunctionPointer & function, const Value * args, std::uint64_t arity) {
		if(function.arity() != arity) throw except::invalid_parameters(arity, function.arity());
		if(function.is_variadic) throw except::invalid_member_access();
		for(std::uint64_t i = 0; i < arity; i++) {
			core.stack.push(args[i]);
		}
		const auto prev = core.pc;
		auto * entry = core.function_pool[function.index];
		core.pc = core.code_begin + entry->address;
		core.stack.push_frame(core.code_end - 1, arity, entry); 
		for(const auto c : function.captured) core.stack.push(c);
		auto result = run_core(core);
		core.pc = prev;
		return result;
	}



	Value invoke_native_function_immediatly(VMCore & core, const NativeFunctionPointer & function, const Value * args, std::uint64_t arity) {
		std::vector<Value> args_vector = { args, args + arity };
		if(arity >= function.arity() && function.is_variadic) {
			Tuple tuple {read_from_stack(core.stack, arity - function.arity())};
			args_vector.push_back(value::tuple(core.heap.alloc(std::move(tuple))));
		}
		else if(arity != function.arity()) {
			throw except::invalid_parameters(function.arity(), arity);
		}


		Context context = wrap_context(core);
		GCLock gc_lock{&function, &core};
		Value return_value = function.handle(&context, args_vector.data());
		return return_value;
	}



	Value invoke_function_immediatly(VMCore & core, const Value & ref, const Value * args, std::uint64_t arity) {

		if (is_script_function(ref)) {
			ScriptFunctionPointer * function = value::as<ScriptFunctionPointer>(ref);
			return invoke_script_function_immediatly(core, *function, args, arity);
		}
		if (is_native_function(ref)) {
			NativeFunctionPointer * function = value::as<NativeFunctionPointer>(ref);
			return invoke_native_function_immediatly(core, *function, args, arity);
		}
		else {
			throw except::invalid_argument();
		}
	}



	void invoke_script_function(VMCore & core, const Value ref_fx, std::uint64_t arity) {
		prepare_args(core, ref_fx, arity);

		const auto & fxptr = *value::as<ScriptFunctionPointer>(ref_fx);
		const auto call_arity = fxptr.arity() + fxptr.is_variadic;
		const auto * entry = core.function_pool[fxptr.index];
		load_onto_stack(core.stack, fxptr.captured);
		core.stack.push_frame(core.pc, call_arity + fxptr.captured.size(), entry);
		core.pc = core.code_begin + entry->address;
	}



	void invoke_native_function(VMCore & core, const Value ref_fx, std::uint64_t arity) {
		std::vector<Value> args = read_from_stack(core.stack, arity);
		const NativeFunctionPointer * fxptr = value::as<NativeFunctionPointer>(ref_fx);
		core.stack.push(invoke_native_function_immediatly(core, *fxptr, args.data(), args.size()));
	}
	
	
	
	void invoke_coroutine(VMCore & core, const Value ref, std::uint64_t arity) {
		if(arity != 0) throw except::invalid_parameters(0, arity);
		auto * coroutine = value::as<Coroutine>(ref);
		core.stack.push_frame(core.pc, 0, coroutine->context);
		for(std::size_t i = 0; i < std::size(coroutine->local_variables) - coroutine->context->frame_size; ++i) {
			core.stack.push(value::null);
		}
		for(std::size_t i = 0; i < std::size(coroutine->local_variables); ++i) {
			core.stack.write(i, coroutine->local_variables[i]);
		}
		core.pc = coroutine->resume_address;
	}



	void invoke_function(VMCore & core, const Value ref_fx, std::uint64_t arity) {
		if(is_script_function(ref_fx)) {
			return invoke_script_function(core, ref_fx, arity);
		}
		else if (is_native_function(ref_fx)) {
			return invoke_native_function(core, ref_fx, arity);
		}
		else if(is_coroutine(ref_fx)) {
			return invoke_coroutine(core, ref_fx, arity);
		}
		else {
			throw except::invalid_argument();
		}
	}
}