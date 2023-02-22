#include "traits.hxx"

namespace ltn::c::type {
	bool is_error(const Type & x) {
		return x.as<Error>();
	}


	bool is_optional(const Type & x) {
		return x.as<Optional>();
	}



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



	bool is_subint(const Type & x) {
		return is_bool(x) || is_char(x);
	}



	bool is_integral(const Type & x) {
		return is_subint(x) || is_int(x);
	}

	

	bool is_numeric(const Type & x) {
		return is_integral(x) || is_float(x);
	}

	
	
	bool is_string(const Type & x) {
		return x.as<String>();
	}



	bool is_array(const Type & x) {
		return x.as<Array>();
	}



	bool is_tuple(const Type & x) {
		return x.as<Tuple>();
	}



	bool is_empty_array(const Type & x) {
		return is_array(x) && (!x.as<Array>()->contains);
	}



	bool is_numeric_array(const Type & type) {
		return is_array(type) 
			&& !is_empty_array(type)
			&& is_numeric(*type.as<Array>()->contains);
	}



	bool is_subtype_array(const Type & from, const Type & to) {	
		if(is_array(to) && is_empty_array(from)) return true;
		if(is_array(to) && is_array(from)) {
			if(is_any(*to.as<Array>()->contains)) return true;
			else return is_subtype_array(
				*from.as<Array>()->contains,
				*to.as<Array>()->contains);
			}
		return false;
	}
}