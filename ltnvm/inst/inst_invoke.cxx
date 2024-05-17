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



		void do_invoke_fxptr(VMCore & core, const Value ref_fx, std::uint64_t arity) {
			const auto & fxptr = core.heap.read<FxPointer>(ref_fx);
			const auto call_arity = fxptr.arity() + fxptr.is_variadic;

			if(arity >= fxptr.arity() && fxptr.is_variadic) {
				Tuple tuple {read_from_stack(core.stack, arity - fxptr.arity())};
				core.stack.push(value::tuple(core.heap.alloc(std::move(tuple))));
			}
			else if(arity < fxptr.arity()) {
				throw except::invalid_parameters(fxptr.arity(), arity);
			}

			const auto * entry = core.function_table[fxptr.index];
			// std::cout << entry->name << "\n";
			load_onto_stack(core.stack, fxptr.captured);
			core.stack.push_frame(core.pc, call_arity + fxptr.captured.size(), entry);
			core.pc = core.code_begin + entry->address;
		}



		void do_invoke_external(VMCore & core, const Value ref_fx, std::uint64_t arity, const std::vector<Value> & args) {
			if(core.fx_table_ltn_to_cxx.contains(ref_fx.i)) {
				auto & fxptr = core.fx_table_ltn_to_cxx.at(ref_fx.i);
				if(arity == fxptr.arity()) {
					ext::Parameters parameters{core.heap, args};
					auto result = fxptr(parameters, core.heap);
					core.stack.push(result);
				}
				else throw except::invalid_parameters(fxptr.arity(), arity);
			}
			else throw except::invalid_argument();
		}



		void do_invoke_coroutine(VMCore & core, const Value ref, std::uint64_t arity) {
			if(arity != 0) throw except::invalid_parameters(0, arity);
			auto * coroutine = ref.as<Coroutine>();
			core.stack.push_frame(core.pc, 0, coroutine->entry);
			for(std::size_t i = 0; i < std::size(coroutine->local_variables) - coroutine->entry->frame_size; ++i) {
				core.stack.push(value::null);
			}
			std::cout << std::size(coroutine->local_variables) << "|" << coroutine->entry->frame_size << "\n";
			for(std::size_t i = 0; i < std::size(coroutine->local_variables); ++i) {
				core.stack.write(i, coroutine->local_variables[i]);
			}
			core.pc = coroutine->resume_address;
		}
	}



	void invoke(VMCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		if(is_fxptr(ref_fx)) {
			return do_invoke_fxptr(core, ref_fx, arity);
		}
		
		else if(is_int(ref_fx)) {
			auto args = read_from_stack(core.stack, arity);
			return do_invoke_external(core, ref_fx, arity, args);
		}
		
		if(is_coroutine(ref_fx)) {
			return do_invoke_coroutine(core, ref_fx, arity);
		}

		else throw except::invalid_argument();
	}



	void invoke_variadic(VMCore & core) {
		const auto ref_param = core.stack.pop();
		const auto ref_fx = core.stack.pop();
		if(is_array(ref_param) || is_tuple(ref_param)) {
			const auto & args = core.heap.read<Contiguous>(ref_param);
			const auto arity = std::size(args);

			if(is_fxptr(ref_fx)) {
				load_onto_stack(core.stack, args);
				return do_invoke_fxptr(core, ref_fx, arity);
			}
			else if(is_int(ref_fx)) {
				return do_invoke_external(core, ref_fx, arity, args.get_underlying());
			}
			else throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}
}