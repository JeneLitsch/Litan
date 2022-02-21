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

}