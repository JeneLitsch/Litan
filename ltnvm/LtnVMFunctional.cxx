#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <sstream>
namespace ltn::vm {
	namespace {
		inline void loadParametersIntoRegister(Register & reg, const auto & params) {
			for(const auto param : params) {
				reg.push(param);
			}
		}

		inline void loadCapturesIntoRegister(Register & reg, const auto & captured) {
			const auto begin = captured.rbegin();
			const auto end = captured.rend();
			for (auto i = begin; i != end; ++i ) { 
				reg.push(*i);
			}
		}
	}

	void LtnVM::invoke() {
		const auto refParam = this->reg.pop();
		const auto refFx = this->reg.pop();
		if(isArr(refParam)) {
			const auto & params = this->heap.read<Array>(refParam.u);

			// Call functions pointer
			if(isFxPtr(refFx)) {
				const auto & fxPtr = this->heap.read<FxPointer>(refFx.u);
				if(params.arr.size() == fxPtr.getParameters()) {
					loadParametersIntoRegister(this->reg, params.arr);
					loadCapturesIntoRegister(this->reg, fxPtr.captured);
					this->stack.pushFrame(this->pc);
					this->pc = fxPtr.address;
				}
				else throw except::invalidParameters(fxPtr.getParameters(), params.arr.size());
			}

			// Call external binding
			else if(isExt(refFx) || isInt(refFx)) {
				auto & fxPtr = *this->externals.at(refFx.i);
				if(params.arr.size() == fxPtr.getParameters()) {
					ext::Api api{this->heap, this->reg, params.arr};
					fxPtr(api);
				}
				else throw except::invalidParameters(fxPtr.getParameters(), params.arr.size());
			}

			// Non callable
			else throw except::invalidArgument();
		}
		else throw except::invalidArgument();
	}

	void LtnVM::external() {
		const auto value = this->reg.pop();
		if(isInt(value)) {
			this->reg.push({value.u, Value::Type::EXTERNAL});
		}
		else throw except::invalidCast("External");
	}



	void LtnVM::capture() {
		const auto var = this->reg.pop();
		const auto fxPtr = this->reg.peek();
		if(isFxPtr(fxPtr)) {
			auto & lambda = this->heap.read<FxPointer>(fxPtr.u);
			lambda.captured.push_back(var);
		}
		else throw except::invalidArgument();
	}
}