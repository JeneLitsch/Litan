#include "instructions.hxx"

namespace ltn::vm::inst {
	namespace {
		inline void load_arguments_onto_stack(Stack & stack, const auto & params) {
			for(const auto param : params) {
				stack.push(param);
			}
		}

		inline void load_captures_into_register(Stack & stack, const auto & captured) {
			for(const auto c : captured) {
				stack.push(c);
			}
		}
	}

	void invoke(VmCore & core) {
		const auto ref_param = core.stack.pop();
		const auto refFx = core.stack.pop();
		if(is_array(ref_param)) {
			const auto & arguments = core.heap.read<Array>(ref_param.u);

			// Call functions pointer
			if(is_fxptr(refFx)) {
				const auto & fxptr = core.heap.read<FxPointer>(refFx.u);
				const auto arity = arguments.size();
				if(arity == fxptr.get_parameters()) {
					core.stack.push_frame(core.pc, static_cast<std::uint8_t>(0));
					load_captures_into_register(core.stack, fxptr.captured);
					load_arguments_onto_stack(core.stack, arguments);
					core.pc = fxptr.address;
				}
				else throw except::invalid_parameters(fxptr.get_parameters(), arity);
			}

			// Call external binding
			else if(is_external(refFx) || is_int(refFx)) {
				if(core.externals.contains(refFx.i)) {
					auto & fxptr = core.externals.at(refFx.i);
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