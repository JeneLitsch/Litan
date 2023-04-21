#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		inline void load_arguments_onto_stack(Stack & stack, const auto & params) {
			for(const auto param : params) {
				stack.push(param);
			}
		}

		inline void load_captures_onto_stack(Stack & stack, const auto & captured) {
			for(const auto c : captured) {
				stack.push(c);
			}
		}
	}

	void invoke(VmCore & core) {
		const auto arity = core.fetch_byte();
		const auto ref_fx = core.stack.pop();

		// Call functions pointer
		if(is_fxptr(ref_fx)) {
			const auto & fxptr = core.heap.read<FxPointer>(ref_fx.u);
			if(arity == fxptr.get_parameters()) {
				core.stack.push_frame(core.pc, static_cast<std::uint8_t>(arity));
				load_captures_onto_stack(core.stack, fxptr.captured);
				core.pc = fxptr.ptr;
			}
			else throw except::invalid_parameters(fxptr.get_parameters(), arity);
		}

		// Call external binding
		else if(is_int(ref_fx)) {
			if(core.externals.contains(ref_fx.i)) {
				auto & fxptr = core.externals.at(ref_fx.i);
				std::vector<Value> args;
				for(std::size_t i = 0; i < arity; ++i) {
					args.push_back(core.stack.pop());
				}
				std::reverse(std::begin(args), std::end(args));
				if(arity == fxptr.arity()) {
					ext::Parameters parameters{core.heap, args};
					auto result = fxptr(parameters, core.heap);
					core.stack.push(result);
				}
				else throw except::invalid_parameters(fxptr.arity(), arity);
			}
			else throw except::invalid_argument();
		}
		// Non callable
		else throw except::invalid_argument();
	}



	void invoke_variadic(VmCore & core) {
		const auto ref_param = core.stack.pop();
		const auto ref_fx = core.stack.pop();
		if(is_array(ref_param)) {
			const auto & arguments = core.heap.read<Array>(ref_param.u);

			// Call functions pointer
			if(is_fxptr(ref_fx)) {
				const auto & fxptr = core.heap.read<FxPointer>(ref_fx.u);
				const auto arity = arguments.size();
				if(arity == fxptr.get_parameters()) {
					core.stack.push_frame(core.pc, static_cast<std::uint8_t>(0));
					load_arguments_onto_stack(core.stack, arguments);
					load_captures_onto_stack(core.stack, fxptr.captured);
					core.pc = fxptr.ptr;
				}
				else throw except::invalid_parameters(fxptr.get_parameters(), arity);
			}

			// Call external binding
			else if(is_int(ref_fx)) {
				if(core.externals.contains(ref_fx.i)) {
					auto & fxptr = core.externals.at(ref_fx.i);
					if(arguments.size() == fxptr.arity()) {
						ext::Parameters parameters{core.heap, arguments};
						auto result = fxptr(parameters, core.heap);
						core.stack.push(result);
					}
					else throw except::invalid_parameters(fxptr.arity(), arguments.size());
				}
				else throw except::invalid_argument();
			}
			// Non callable
			else throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}
}