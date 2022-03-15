#include "convert.hxx"
#include "type_check.hxx"
#include "Exception.hxx"

namespace ltn::vm::convert {


	bool to_bool(const Value value) {
		if(is_bool(value)) {
			return value.b;
		}

		if(is_char(value)) {
			return value.c;
		}

		if(is_int(value)) {
			return value.i;
		}
		
		if(is_float(value)) {
			return value.f != 0.0;
		}

		if(is_null(value)) {
			return false;
		}

		return true;
	}


	std::int64_t to_int(const Value value) {
		if(is_bool(value)) {
			return value.b;
		}	

		if(is_char(value)) {
			return value.i;
		}

		if(is_int(value)) {
			return value.i;
		}
		
		throw except::invalid_cast("Int");
	}


	stx::float64_t to_float(const Value value) {
		if(is_bool(value)) {
			return static_cast<stx::float64_t>(value.b);
		}

		if(is_char(value)) {
			return static_cast<stx::float64_t>(value.c);
		}

		if(is_int(value)) {
			return static_cast<stx::float64_t>(value.i);
		}

		if(is_float(value)) {
			return value.f;
		}
		throw except::invalid_cast("Float");
	}


	char to_char(const Value value) {
		if(is_char(value)) {
			return value.c;
		}

		throw except::invalid_cast("Char");
	}


	std::string to_string(Value value, Heap & heap) {
		if(is_string(value)) {
			return heap.read<String>(value.u).str;
		}

		throw except::invalid_cast("String");
	}
}