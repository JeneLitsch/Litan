#include "Stringify.hxx"
#include "TypeCheck.hxx"
#include <sstream>
namespace ltn::vm {
	std::string toString(const Value & value, Heap & heap) {
		if(isNull(value)) {
			return "null";
		}
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
			return heap.read<String>(value.u).str;
		}
		if(isArr(value)) {
			const auto & arr = heap.read<Array>(value.u);
			std::stringstream ss;
			ss << "[";
			for(std::size_t i = 0; i < arr.arr.size(); i++) {
				ss << ((i) ? (", ") : (""));
				ss << toString(arr.arr[i], heap);
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
		throw std::runtime_error{"Cannot convert to string"};
	}
}