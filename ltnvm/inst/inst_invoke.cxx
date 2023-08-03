#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		inline void load_onto_stack(Stack & stack, const auto & values) {
			for(const auto c : values) {
				stack.push(c);
			}
		}



		std::vector<Value> read_from_stack(Stack & stack, std::uint64_t arity) {
			std::vector<Value> args;
			for(std::size_t i = 0; i < arity; ++i) {
				args.push_back(stack.pop());
			}
			std::reverse(std::begin(args), std::end(args));
			return args;
		}



		void do_invoke_fxptr(VmCore & core, const Value ref_fx, std::uint64_t arity) {
			const auto & fxptr = core.heap.read<FxPointer>(ref_fx);
			const auto call_arity = fxptr.arity() + fxptr.is_variadic;

			if(arity >= fxptr.arity() && fxptr.is_variadic) {
				Tuple tuple {read_from_stack(core.stack, arity - fxptr.arity())};
				core.stack.push(value::tuple(core.heap.alloc(std::move(tuple))));
			}
			else if(arity < fxptr.arity()) {
				throw except::invalid_parameters(fxptr.arity(), arity);
			}

			core.stack.push_frame(core.pc, call_arity);
			load_onto_stack(core.stack, fxptr.captured);
			core.pc = fxptr.ptr;
		}



		void do_invoke_external(VmCore & core, const Value ref_fx, std::uint64_t arity, const std::vector<Value> & args) {
			if(core.externals.contains(ref_fx.i)) {
				auto & fxptr = core.externals.at(ref_fx.i);
				if(arity == fxptr.arity()) {
					ext::Parameters parameters{core.heap, args};
					auto result = fxptr(parameters, core.heap);
					core.stack.push(result);
				}
				else throw except::invalid_parameters(fxptr.arity(), arity);
			}
			else throw except::invalid_argument();
		}
	}



	void invoke(VmCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		if(is_fxptr(ref_fx)) {
			return do_invoke_fxptr(core, ref_fx, arity);
		}
		else if(is_int(ref_fx)) {
			auto args = read_from_stack(core.stack, arity);
			return do_invoke_external(core, ref_fx, arity, args);
		}
		else throw except::invalid_argument();
	}



	void invoke_variadic(VmCore & core) {
		const auto ref_param = core.stack.pop();
		const auto ref_fx = core.stack.pop();
		if(is_array(ref_param) || is_tuple(ref_param)) {
			const auto & args = core.heap.read<Contiguous>(ref_param);
			const auto arity = std::size(args.data);

			if(is_fxptr(ref_fx)) {
				load_onto_stack(core.stack, args);
				return do_invoke_fxptr(core, ref_fx, arity);
			}
			else if(is_int(ref_fx)) {
				return do_invoke_external(core, ref_fx, arity, args.data);
			}
			else throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}
}