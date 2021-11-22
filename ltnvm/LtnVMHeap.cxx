#include "LtnVM.hxx"
#include "TypeCheck.hxx"

namespace ltn::vm {
	void LtnVM::allocStr() {
		const auto ptr = this->heap.allocString();
		this->reg.push({ ptr, Value::Type::STRING });
	}

	void LtnVM::ch4r() {
		const auto chr = this->fetchByte();
		const auto ptr = this->reg.peek();
		std::string & str = this->heap.readString(ptr.u);
		str.push_back(static_cast<char>(chr));
	}

	void LtnVM::allocArr() {
		const auto ptr = this->heap.allocArray();
		this->reg.push({ ptr, Value::Type::ARRAY });
	}
}