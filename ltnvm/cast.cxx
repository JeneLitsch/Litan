#include "cast.hxx"
#include "type_check.hxx"
#include "Exception.hxx"
#include "convert.hxx"
#include "stdxx/float64_t.hxx"

namespace ltn::vm::cast {
	namespace {
		template<typename To>
		To parse_value(const std::string & str) {
			To to;
			std::stringstream ss{str};
			ss >> to;
			if(ss.fail()) {
				throw except::invalid_argument("Cannot parse string to value");
			}
			return to;
		}
	}


	std::string to_string(Value value, Heap & heap) {
		return convert::to_string(value, heap);
	}


	Array to_array(Value value) {
		return {value};
	}

	std::int64_t to_int(Value value) {
		if(is_float(value)) {
			return static_cast<std::int64_t>(value.f);
		}
		
		return convert::to_int(value);
	}



	stx::float64_t to_float(Value value, Heap & heap) {
		if (is_clock(value)) {
			const auto & clock = heap.read<Clock>(value.u);
			return clock.getSeconds();
		}

		return convert::to_float(value);
	}


	bool to_bool(Value value) {
		return convert::to_bool(value);
	}

	char to_char(Value value) {
		if(is_int(value)) {
			return static_cast<char>(value.i);
		}

		if(is_float(value)) {
			return static_cast<char>(value.f);
		}

		return convert::to_char(value);
	}
}