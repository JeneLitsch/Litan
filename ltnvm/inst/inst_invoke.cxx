#include "instructions.hxx"
#include "c_api.hxx"

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



		void invoke_fxptr(VmCore & core, const Value & ref_fx, const Array & arguments) {
			const auto & fxptr = core.heap.read<FxPointer>(ref_fx.u);
			const auto arity = arguments.size();
			if(arity == fxptr.get_parameters()) {
				core.stack.push_frame(core.pc, static_cast<std::uint8_t>(0));
				load_captures_into_register(core.stack, fxptr.captured);
				load_arguments_onto_stack(core.stack, arguments);
				core.pc = fxptr.ptr;
			}
			else throw except::invalid_parameters(fxptr.get_parameters(), arity);
		}



		void invoke_external(VmCore & core, const Value & ref_fx, const Array & arguments) {
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



		void invoke_library(VmCore & core, const Value & ref_fx, const Array & arguments) {
			const auto & fxptr = core.heap.read<LibraryFx>(ref_fx.u);
			const auto arity = arguments.size();
			CoreWrapper wrapper = wrap_core(core.heap, arguments, fxptr.library);
			ltn_CApi api = bind_api(wrapper);
			fxptr.fx_ptr(&api);
			core.stack.push(wrapper.return_value);
		}
	}

	

	void invoke(VmCore & core) {
		const auto ref_param = core.stack.pop();
		const auto refFx = core.stack.pop();
		if(is_array(ref_param)) {
			const auto & arguments = core.heap.read<Array>(ref_param.u);
			if(is_fxptr(refFx))      return invoke_fxptr(core, refFx, arguments);
			if(is_external(refFx))   return invoke_external(core, refFx, arguments);
			if(is_int(refFx))        return invoke_external(core, refFx, arguments);
			if(is_library_fx(refFx)) return invoke_library(core, refFx, arguments);
			throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}
}