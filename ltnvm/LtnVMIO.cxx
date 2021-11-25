#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "Stringify.hxx"

namespace ltn::vm {
	// void LtnVM::outValue(const Value & value) {
	// 	auto & out = this->ostream.get();
	// 	switch (value.type) {
	// 		case Value::Type::INT:
	// 			out << value.i;
	// 			break;
			
	// 		case Value::Type::FLOAT:
	// 			out << value.f;
	// 			break;

	// 		case Value::Type::BOOL:
	// 			out << std::boolalpha << value.b;
	// 			break;

	// 		case Value::Type::NVLL:
	// 			out << "null";
	// 			break;

	// 		case Value::Type::ADDR:
	// 			out << "addr:" << value.u;
	// 			break;

	// 		case Value::Type::ARRAY: {
	// 			const auto & arr = this->heap.readArray(value.u);
	// 			out << "[";
	// 			for(std::size_t i = 0; i < arr.size(); i++) {
	// 				out << ((i) ? (", ") : (""));
	// 				this->outValue(arr[i]);
	// 			}
	// 			out << "]";
	// 		} break;

	// 		case Value::Type::STRING: {
	// 			const auto & str = this->heap.readString(value.u);
	// 			this->ostream.get() << str;

	// 		} break;
	// 	}
	// }

	

	void LtnVM::out() {
		const auto value = this->reg.pop();
		const auto ref = this->reg.pop();
		if(isOStream(ref)) {
			auto & ostream = this->heap.readOStream(ref.u).get();
			ostream << toString(value, this->heap); 
		}
		else {
			throw std::runtime_error{"Can only output to ostream"};
		}
	}

	namespace {
		using VT = Value::Type;

		std::istream & getIstream(Heap & heap, Register & reg) {
			const auto ref = reg.pop();
			if(isIStream(ref)) {
				return heap.readIStream(ref.u).get();
			}
			else {
				throw std::runtime_error{"Can only read from istream"};
			}
		}

		void pushString(Heap & heap, Register & reg, const auto & value) {
			const auto addr = heap.allocString(value);
			reg.push(Value{addr, VT::STRING});
		}
	}

	void LtnVM::in_str() {
		auto & in = getIstream(this->heap, this->reg); 
		std::string value;
		in >> value;
		pushString(this->heap, this->reg, value);
	}

	void LtnVM::in_line() {
		auto & in = getIstream(this->heap, this->reg); 
		std::string value;
		std::getline(in, value);
		pushString(this->heap, this->reg, value);
	}

	void LtnVM::in_int() {
		auto & in = getIstream(this->heap, this->reg); 
		std::int64_t value;
		in >> value;
		reg.push(Value{value});
	}

	void LtnVM::in_float() {
		auto & in = getIstream(this->heap, this->reg); 
		double value;
		in >> value;
		reg.push(Value{value});
	}
}