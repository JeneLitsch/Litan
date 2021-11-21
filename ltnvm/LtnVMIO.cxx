#include "LtnVM.hxx"

namespace ltn::vm {
	void LtnVM::out() {
		const auto value = this->reg.pop();
		switch (value.type) {

		case Value::Type::INT:
			this->ostream.get() << value.i;
			break;
		
		case Value::Type::FLOAT:
			this->ostream.get() << value.f;
			break;

		case Value::Type::BOOL:
			this->ostream.get() << std::boolalpha << value.b;
			break;

		case Value::Type::NVLL:
			this->ostream.get() << "null";
			break;

		case Value::Type::REF:
			this->ostream.get() << "ref:" << value.u;
			break;

		case Value::Type::ARRAY:
			this->ostream.get() << "array:" << value.u;
			break;
		}
	}
}