#include "LtnVM.hxx"
#include "type_check.hxx"
#include <sstream>
namespace ltn::vm {
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

	void LtnVM::invoke() {
		const auto ref_param = this->core.reg.pop();
		const auto refFx = this->core.reg.pop();
		if(is_array(ref_param)) {
			const auto & params = this->core.heap.read<Array>(ref_param.u);

			// Call functions pointer
			if(is_fxptr(refFx)) {
				const auto & fxptr = this->core.heap.read<FxPointer>(refFx.u);
				if(params.arr.size() == fxptr.get_parameters()) {
					load_rarameters_into_register(this->core.reg, params.arr);
					load_captures_into_register(this->core.reg, fxptr.captured);
					this->core.stack.push_frame(this->core.pc);
					this->core.pc = fxptr.address;
				}
				else throw except::invalid_parameters(fxptr.get_parameters(), params.arr.size());
			}

			// Call external binding
			else if(is_external(refFx) || is_int(refFx)) {
				if(this->core.externals.contains(refFx.i)) {
					auto & fxptr = *this->core.externals.at(refFx.i);
					if(params.arr.size() == fxptr.get_parameters()) {
						ext::Api api{this->core.heap, this->core.reg, params.arr};
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

	void LtnVM::external() {
		const auto value = this->core.reg.pop();
		if(is_int(value)) {
			this->core.reg.push({value.u, Value::Type::EXTERNAL});
		}
		else throw except::invalid_cast("External");
	}



	void LtnVM::capture() {
		const auto var = this->core.reg.pop();
		const auto fxptr = this->core.reg.peek();
		if(is_fxptr(fxptr)) {
			auto & lambda = this->core.heap.read<FxPointer>(fxptr.u);
			lambda.captured.push_back(var);
		}
		else throw except::invalid_argument();
	}
}