#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>


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
		const auto ref = this->heap.alloc<FxPointer>({address, params});
		this->reg.push(Value{ref, Value::Type::FX_PTR});
	}
	void LtnVM::addr(){
		this->reg.push(Value{this->fetchUint(), Value::Type::ADDR});
	}
	void LtnVM::truE(){
		this->reg.push(Value{true, Value::Type::BOOL});
	}
	void LtnVM::falsE(){
		this->reg.push(Value{false, Value::Type::BOOL});
	}
	void LtnVM::newarr(){
		const auto ptr = this->heap.alloc<Array>({});
		this->reg.push({ ptr, Value::Type::ARRAY });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newstr() {
		const auto ptr = this->heap.alloc<String>({});
		this->reg.push({ ptr, Value::Type::STRING });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newout_std() {
		const auto ptr = this->heap.alloc<OStream>(std::cout);
		this->reg.push({ ptr, Value::Type::OSTREAM });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newin_std() {
		const auto ptr = this->heap.alloc<IStream>(std::cin);
		this->reg.push({ ptr, Value::Type::ISTREAM });
		this->heap.collectGarbage(this->stack, this->reg);
	}
	void LtnVM::newClock() {
		const auto ptr = this->heap.alloc<Clock>({});
		this->reg.push({ ptr, Value::Type::CLOCK });
		this->heap.collectGarbage(this->stack, this->reg);
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
}