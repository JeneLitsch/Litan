#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include <iostream>


namespace ltn::vm {
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
}