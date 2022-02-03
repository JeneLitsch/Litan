#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>
#include <string>

namespace ltn::vm {
	void LtnVM::newi(){
		this->reg.push(Value{this->fetchUint(), Value::Type::INT});
	}
	void LtnVM::newf(){
		this->reg.push(Value{this->fetchUint(), Value::Type::FLOAT});
	}
	void LtnVM::newu(){
		this->reg.push(Value{this->fetchUint(), Value::Type::NVLL});
	}
	void LtnVM::newfx(){
		const auto address = this->fetchUint(); 
		const auto params = this->fetchUint();
		const auto ref = this->heap.alloc<FxPointer>({address, params, {}});
		this->reg.push(Value{ref, Value::Type::FX_PTR});
	}
	void LtnVM::truE(){
		this->reg.push(Value{true, Value::Type::BOOL});
	}
	void LtnVM::falsE(){
		this->reg.push(Value{false, Value::Type::BOOL});
	}
	void LtnVM::null() {
		this->reg.push(Value{false, Value::Type::NVLL});
	}
	void LtnVM::ch4r() {
		const auto chr = this->fetchByte();
		const auto ptr = this->reg.peek();
		auto & str = this->heap.read<String>(ptr.u);
		str.str.push_back(static_cast<char>(chr));
	}
	void LtnVM::elem() {
		const auto value = this->reg.pop();
		const auto ptr = this->reg.peek();
		auto & arr = this->heap.read<Array>(ptr.u);
		arr.arr.push_back(value);
	}

	void LtnVM::char_4() {
		const auto ptr = this->reg.peek();
		auto & str = this->heap.read<String>(ptr.u);
		str.str.append(
			this->byteCode.begin()+static_cast<std::int64_t>(this->pc),
			this->byteCode.begin()+static_cast<std::int64_t>(this->pc+4U));
		this->pc+=4;
	}

	void LtnVM::char_8() {
		const auto ptr = this->reg.peek();
		auto & str = this->heap.read<String>(ptr.u);
		str.str.append(
			this->byteCode.begin()+static_cast<std::int64_t>(this->pc),
			this->byteCode.begin()+static_cast<std::int64_t>(this->pc+8U));
		this->pc+=8;
	}
}