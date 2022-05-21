#include "instructions.hxx"
#include "type_check.hxx"
#include <sstream>
namespace ltn::vm::inst {
	namespace {
		inline void load_rarameters_into_register(Register & reg, const auto & params) {
			for(const auto param : params) {
				reg.push(param);
			}
		}

		inline void load_captures_into_register(Register & reg, const auto & captured) {
			const auto begin = captured.rbegin();
			const auto end = captured.rend();
			for (auto i = begin; i != end; ++i ) { 
				reg.push(*i);
			}
		}
	}

	void invoke(VmCore & core) {
		const auto ref_param = core.reg.pop();
		const auto refFx = core.reg.pop();
		if(is_array(ref_param)) {
			const auto & params = core.heap.read<Array>(ref_param.u);

			// Call functions pointer
			if(is_fxptr(refFx)) {
				const auto & fxptr = core.heap.read<FxPointer>(refFx.u);
				if(params.arr.size() == fxptr.get_parameters()) {
					load_rarameters_into_register(core.reg, params.arr);
					load_captures_into_register(core.reg, fxptr.captured);
					core.stack.push_frame(core.pc);
					core.pc = fxptr.address;
				}
				else throw except::invalid_parameters(fxptr.get_parameters(), params.arr.size());
			}

			// Call external binding
			else if(is_external(refFx) || is_int(refFx)) {
				if(core.externals.contains(refFx.i)) {
					auto & fxptr = *core.externals.at(refFx.i);
					if(params.arr.size() == fxptr.get_parameters()) {
						ext::Api api{core.heap, core.reg, params.arr};
						fxptr(api);
					}
					else throw except::invalid_parameters(fxptr.get_parameters(), params.arr.size());
				}
				else throw except::invalid_argument();
			}
			// Non callable
			else throw except::invalid_argument();
		}
		else throw except::invalid_argument();
	}

	void external(VmCore & core) {
		const auto value = core.reg.pop();
		if(is_int(value)) {
			core.reg.push({value.u, Value::Type::EXTERNAL});
		}
		else throw except::invalid_cast("External");
	}



	void capture(VmCore & core) {
		const auto var = core.reg.pop();
		const auto fxptr = core.reg.peek();
		if(is_fxptr(fxptr)) {
			auto & lambda = core.heap.read<FxPointer>(fxptr.u);
			lambda.captured.push_back(var);
		}
		else throw except::invalid_argument();
	}
}