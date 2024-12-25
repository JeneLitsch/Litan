#include "instructions.hxx"

namespace ltn::vm::inst {


	namespace {
		inline void load_onto_stack(VMStack & stack, const auto & values) {
			for(const auto c : values) {
				stack.push(c);
			}
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


		void do_invoke_script_function(VMCore & core, const Value ref_fx, std::uint64_t arity) {
			prepare_args(core, ref_fx, arity);

			const auto & fxptr = *value::as<ScriptFunctionPointer>(ref_fx);
			const auto call_arity = fxptr.arity() + fxptr.is_variadic;
			const auto * entry = core.function_pool[fxptr.index];
			load_onto_stack(core.stack, fxptr.captured);
			core.stack.push_frame(core.pc, call_arity + fxptr.captured.size(), entry);
			core.pc = core.code_begin + entry->address;
		}


		void do_invoke_native_function(VMCore & core, const Value ref_fx, std::uint64_t arity) {
			prepare_args(core, ref_fx, arity);

			std::vector<Value> args;
			for (std::size_t i = 0; i < arity; i++) {
				args.push_back(core.stack.pop());
			}
			std::reverse(std::begin(args), std::end(args));

			NativeFunctionPointer * fx_ptr = value::as<NativeFunctionPointer>(ref_fx);
			VMCore * core_ptr = &core;
			Context context = {
				.core = static_cast<void*>(core_ptr),
			};
			struct GCLock {
				NativeFunctionPointer * fx_ptr;
				VMCore * core;
				GCLock(NativeFunctionPointer * fx_ptr, VMCore * core)
					: fx_ptr { fx_ptr } 
					, core { core } {
					if (!fx_ptr->uses_gc()) {
						core->heap.lock_gc();
					}
				}
				~GCLock() {
					if (!fx_ptr->uses_gc()) {
						core->heap.unlock_gc();
					}
				}
			};

			GCLock gc_lock{fx_ptr, &core};
			Value return_value = fx_ptr->handle(&context, args.data());
			core.stack.push(return_value);
		}


		void do_invoke_coroutine(VMCore & core, const Value ref, std::uint64_t arity) {
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



	void invoke(VMCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		if(is_script_function(ref_fx)) {
			return do_invoke_script_function(core, ref_fx, arity);
		}
		else if (is_native_function(ref_fx)) {
			return do_invoke_native_function(core, ref_fx, arity);
		}
		
		else if(is_coroutine(ref_fx)) {
			return do_invoke_coroutine(core, ref_fx, arity);
		}

		else throw except::invalid_argument();
	}



	void invoke_variadic(VMCore & core) {
		const auto ref_param = core.stack.pop();
		const auto ref_fx = core.stack.pop();
		if(is_array(ref_param) || is_tuple(ref_param)) {
			const auto & args = *value::as<Contiguous>(ref_param);
			const auto arity = std::size(args);

			if(is_script_function(ref_fx)) {
				load_onto_stack(core.stack, args);
				return do_invoke_script_function(core, ref_fx, arity);
			}
			else throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}
}