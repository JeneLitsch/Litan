#pragma once
#include "Type.hxx"

namespace ltn::c::type {
	
	bool is_error(const Type & x);
	bool is_optional(const Type & x);

	bool is_null(const Type & x);
	bool is_any(const Type & x);

	bool is_bool(const Type & x);
	bool is_char(const Type & x);
	bool is_int(const Type & x);
	bool is_float(const Type & x);

	bool is_subint(const Type & x);
	bool is_integral(const Type & x);
	bool is_numeric(const Type & x);

	bool is_string(const Type & x);
	bool is_array(const Type & x);
	bool is_empty_array(const Type & x);
	bool is_subtype_array(const Type & from, const Type & to);
}