#include "cast.hxx"
#include "TypeCheck.hxx"
#include "Exception.hxx"
#include "convert.hxx"

namespace ltn::vm::cast {
	namespace {
		template<typename To>
		To parseValue(const std::string & str) {
			To to;
			std::stringstream ss{str};
			ss >> to;
			if(ss.fail()) {
				throw except::invalidArgument("Cannot parse string to value");
			}
			return to;
		}
	}


	std::string to_string(Value value, Heap & heap) {
		return convert::to_string(value, heap);
	}


	std::vector<Value> to_array(Value value) {
		return {value};
	}

	std::int64_t to_int(Value value, Heap & heap) {
		if(isFloat(value)) {
			return static_cast<std::int64_t>(value.f);
		}
		
		if(isStr(value)) {
			const auto & str = heap.read<String>(value.u);
			return parseValue<std::int64_t>(str.str); 
		}

		return convert::to_int(value);
	}



	double to_float(Value value, Heap & heap) {
		if(isStr(value)) {
			const auto & str = heap.read<String>(value.u);
			return parseValue<double>(str.str); 
		}
		
		if (isClock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			return clock.getSeconds();
		}

		return convert::to_float(value);
	}


	bool to_bool(Value value) {
		return convert::to_bool(value);
	}

	char to_char(Value value) {
		if(isInt(value)) {
			return static_cast<char>(value.i);
		}

		if(isFloat(value)) {
			return static_cast<char>(value.f);
		}

		return convert::to_char(value);
	}
}