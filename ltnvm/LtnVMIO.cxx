#include "LtnVM.hxx"

namespace ltn::vm {
	void LtnVM::outValue(const Value & value) {
		auto & out = this->ostream.get();
		switch (value.type) {
			case Value::Type::INT:
				out << value.i;
				break;
			
			case Value::Type::FLOAT:
				out << value.f;
				break;

			case Value::Type::BOOL:
				out << std::boolalpha << value.b;
				break;

			case Value::Type::NVLL:
				out << "null";
				break;

			case Value::Type::ADDR:
				out << "addr:" << value.u;
				break;

			case Value::Type::ARRAY: {
				const auto & arr = this->heap.readArray(value.u);
				out << "[";
				for(std::size_t i = 0; i < arr.size(); i++) {
					out << ((i) ? (", ") : (""));
					this->outValue(arr[i]);
				}
				out << "]";
			} break;

			case Value::Type::STRING: {
				const auto & str = this->heap.readString(value.u);
				this->ostream.get() << str;

			} break;
		}
	}


	void LtnVM::out() {
		const auto value = this->reg.pop();
		this->outValue(value);
	}
}