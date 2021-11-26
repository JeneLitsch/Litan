#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <sstream>

namespace ltn::vm {
	bool isTruthy(const Value & value) {
		if(isBool(value)) return value.b;
		if(isInt(value)) return value.i;
		if(isFloat(value)) return value.f;
		throw std::runtime_error{"Cannot convert to bool"};
	}

	void LtnVM::jump() {
		const auto addr = this->fetchUint(); 
		this->pc = addr;
	}
	void LtnVM::call() {
		const auto addr = this->fetchUint(); 
		this->stack.pushFrame(this->pc);
		this->pc = addr;
	}
	void LtnVM::reTurn() {
		this->pc = this->stack.popFrame();
	}
	void LtnVM::iF() {
		const auto value = this->reg.pop();
		const auto elseAddr = this->fetchUint();
		if(!isTruthy(value)) {
			this->pc = elseAddr;
		}
	}
	void LtnVM::error() {
		throw std::runtime_error{"An error was thrown during runtime"};
	}
	void LtnVM::invoke() {
		const auto refParam = this->reg.pop();
		const auto refFx = this->reg.pop();
		if(isFxPtr(refFx)) {
			const auto & fxPtr = this->heap.readFxPointer(refFx.u);
			if(isArr(refParam)) {
				const auto & params = this->heap.readArray(refParam.u);
				if(params.size() == fxPtr.params) {
					for(const auto param : params) {
						this->reg.push(param);
					}
					this->stack.pushFrame(this->pc);
					this->pc = fxPtr.address;
				}
				else {
					std::stringstream ss;
					ss << "Invoked fx with wrong number of paramters.";
					ss << "Got " << params.size() << " expected " << fxPtr.params;
					throw std::runtime_error{ss.str()};
				} 
			}
			else throw std::runtime_error{"invoke needs an array of parameters"};
		}
		else throw std::runtime_error{"Can only invoke fxPtr"};
	}
}