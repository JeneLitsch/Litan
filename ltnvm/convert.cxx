#include "convert.hxx"
#include "TypeCheck.hxx"
#include "Exception.hxx"

namespace ltn::vm::convert {
	bool to_bool(const Value value) {
		if(isBool(value)) {
			return value.b;
		}

		if(isChar(value)) {
			return value.c;
		}

		if(isInt(value)) {
			return value.i;
		}
		
		if(isFloat(value)) {
			return value.f != 0.0;
		}

		if(isNull(value)) {
			return false;
		}

		return true;
	}

	std::int64_t to_int(const Value value) {
		if(isBool(value)) {
			return value.b;
		}	

		if(isChar(value)) {
			return value.i;
		}		
		
		if(isInt(value)) {
			return value.i;
		}
		
		throw except::invalidCast("Int");
	}

	double to_float(const Value value) {
		if(isBool(value)) {
			return static_cast<double>(value.b);
		}

		if(isChar(value)) {
			return static_cast<double>(value.c);
		}

		if(isInt(value)) {
			return static_cast<double>(value.i);
		}
		
		if(isFloat(value)) {
			return value.f;
		}
		throw except::invalidCast("Float");
	}

	char to_char(const Value value) {
		if(isChar(value)) {
			return value.c;
		}

		throw except::invalidCast("Char");
	}

	std::string to_string(Value value, Heap & heap) {
		if(isNull(value)) {
			return "null";
		}
		if(isBool(value)) {
			std::stringstream ss;
			ss << std::boolalpha << value.b;
			return ss.str();
		}
		if(isChar(value)) {
			return std::string(1, value.c);
		}
		if(isInt(value)) {
			std::stringstream ss;
			ss << value.i;
			return ss.str();
		}
		if(isFloat(value)) {
			std::stringstream ss;
			ss << value.f;
			return ss.str();
		}
		if(isStr(value)) {
			return heap.read<String>(value.u).str;
		}
		if(isArr(value)) {
			const auto & arr = heap.read<Array>(value.u);
			std::stringstream ss;
			ss << "[";
			for(std::size_t i = 0; i < arr.arr.size(); i++) {
				ss << ((i) ? (", ") : (""));
				ss << to_string(arr.arr[i], heap);
			}
			ss << "]";
			return ss.str();
		}
		if(isRange(value)) {
			const auto & range = heap.read<Range>(value.u);
			const auto & array = heap.read<Array>(range.array);
			std::stringstream ss;
			ss << "[";
			for(std::int64_t i = range.begin; i < range.end; i++) {
				ss << ((i != range.begin) ? (", ") : (""));
				ss << to_string(array.arr[i], heap);
			}
			ss << "]";
			return ss.str();
		}
		if(isOStream(value)) {
			return "<ostream>";
		}
		if(isIStream(value)) {
			return "<istream>";
		}
		if(isFxPtr(value)) {
			const auto & fxPtr = heap.read<FxPointer>(value.u);
			std::stringstream ss;
			ss << "<fx:";
			ss << fxPtr.address << "," << fxPtr.params << ">";
			return  ss.str();
		}
		if(isClock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			std::stringstream ss;
			ss << "<clock: " << clock.getSeconds() << "s>";
			return ss.str();
		}
		if(isStruct(value)) {
			return "<struct>";
		}
		throw except::invalidCast("String");
	}

}