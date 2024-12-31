#include "function.hxx"
#include "GCLock.hxx"

namespace ltn::vm {
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



	Value invoke_native_function_recursive(VMCore & core, const Value ref_fx, std::uint64_t arity) {
		prepare_args(core, ref_fx, arity);

		std::vector<Value> args;
		for (std::size_t i = 0; i < arity; i++) {
			args.push_back(core.stack.pop());
		}
		std::reverse(std::begin(args), std::end(args));

		NativeFunctionPointer * fx_ptr = value::as<NativeFunctionPointer>(ref_fx);
		Context context = wrap_context(core);
		GCLock gc_lock{fx_ptr, &core};
		Value return_value = fx_ptr->handle(&context, args.data());
		return return_value;
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
		core.stack.push(invoke_native_function_recursive(core, ref_fx, arity));
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
}