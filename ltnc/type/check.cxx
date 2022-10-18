#include "check.hxx"

namespace ltn::c::type {

	bool is_null(const Type & x) {
		return x.as<Null>();
	}



	bool is_any(const Type & x) {
		return x.as<Any>();
	}



	bool is_bool(const Type & x) {
		return x.as<Bool>();
	}



	bool is_char(const Type & x) {
		return x.as<Char>();
	}



	bool is_int(const Type & x) {
		return x.as<Int>();
	}



	bool is_float(const Type & x) {
		return x.as<Float>();
	}



	bool is_integral(const Type & x) {
		return is_bool(x) || is_char(x) || is_int(x);
	}



	bool is_numeric(const Type & x) {
		return is_integral(x) || is_float(x);
	}


	bool is_convertible(const Type & from, const Type & to) {
		if(is_any(to)) return true;
		return from == to;
	}
}