#include "convert.hxx"
#include "TypeCheck.hxx"
#include "Exception.hxx"

namespace ltn::vm::convert {
	namespace {
		auto print_element(const Value value, Heap & heap) {
			return convert::to_string(value, heap);
		} 

		auto print_element(const std::pair<Value, Value> pair, Heap & heap) {
			std::ostringstream ss;
			const auto & [key, val] = pair;
			ss << to_string(key, heap) << " : " << to_string(val, heap);
			return ss.str();
		}

		template<typename Iterator>
		void print_all(
			Iterator begin,
			Iterator end,
			std::ostream & out,
			Heap & heap,
			char open = '[',
			char close = ']') {
			
			out << open;
			for(auto it = begin; it != end; ++it) {
				if (it != begin) out << ", ";
				out << print_element(*it, heap);
			}
			out << close;
		}
	}


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
			const auto & array = heap.read<Array>(value.u).get();
			std::stringstream ss;
			print_all(std::begin(array), std::end(array), ss, heap);
			return ss.str();
		}

		if(isRange(value)) {
			const auto & range = heap.read<Range>(value.u);
			const auto & array = heap.read<Array>(range.array).get();
			auto begin = std::begin(array) + range.begin;
			auto end = std::begin(array) + range.end;
			std::stringstream ss;
			print_all(begin, end, ss, heap);
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
			std::ostringstream ss;
			ss << "<fx:";
			ss << fxPtr.address << "," << fxPtr.params << ">";
			return  ss.str();
		}

		if(isClock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			std::ostringstream ss;
			ss << "<clock: " << clock.getSeconds() << "s>";
			return ss.str();
		}

		if(isStruct(value)) {
			return "<struct>";
		}

		if(isQueue(value)) {
			const auto & deque = heap.read<Deque>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(isStack(value)) {
			const auto & deque = heap.read<Deque>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(deque), std::end(deque), ss, heap, '<', '>');
			return ss.str();
		}

		if(isMap(value)) {
			const auto & map = heap.read<Map>(value.u).get();
			std::ostringstream ss;
			print_all(std::begin(map), std::end(map), ss, heap, '{', '}');
			return ss.str();
		}

		throw except::invalidCast("String");
	}
}