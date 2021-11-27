#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <sstream>
namespace ltn::vm {
	namespace {
		std::runtime_error wrongParameterCount(
			const auto & got, const auto & callable,
			const std::string_view calledType) {
			std::stringstream ss;
			ss	<< "Invoked " << calledType
				<< " with wrong number of paramters. ";
			
			ss	<< "Got " << got.arr.size()
				<< " expected " << callable.getParameters();
			return std::runtime_error{ss.str()};
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
					for(const auto param : params.arr) {
						this->reg.push(param);
					}
					this->stack.pushFrame(this->pc);
					this->pc = fxPtr.address;
				}
				else {
					throw wrongParameterCount(params, fxPtr, "function pointer");
				} 
			}

			// Call external binding
			else if(isExt(refFx)) {
				auto & fxPtr = *this->externals.at(refFx.u);
				if(params.arr.size() == fxPtr.getParameters()) {
					ext::Api api{this->heap, this->reg, params.arr};
					fxPtr(api);
					this->reg.push(value::null);
				}
				else {
					throw wrongParameterCount(params, fxPtr, "external");
				} 
			}

			// Non callable
			else throw std::runtime_error{"Can only invoke fxPtr or external"};
		}
		else throw std::runtime_error{"invoke needs an array of parameters"};
	}
	void LtnVM::external() {
		const auto value = this->reg.pop();
		if(isInt(value)) {
			this->reg.push({value.u, Value::Type::EXTERNAL});
		}
		else throw std::runtime_error{"Cannot convert to external"};
	}
}