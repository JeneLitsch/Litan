#include "Stringify.hxx"
#include "TypeCheck.hxx"
#include <sstream>
namespace ltn::vm {
	std::string toString(const Value & value, Heap & heap) {
		if(isBool(value)) {
			std::stringstream ss;
			ss << std::boolalpha << value.b;
			return ss.str();
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
			return heap.readString(value.u);
		}
		if(isArr(value)) {
			const auto & arr = heap.readArray(value.u);
			std::stringstream ss;
			ss << "[";
			for(std::size_t i = 0; i < arr.size(); i++) {
				ss << ((i) ? (", ") : (""));
				ss << toString(arr[i], heap);
			}
			ss << "]";
			return ss.str();
		}
		throw std::runtime_error{"Cannot convert to string"};
	}
}