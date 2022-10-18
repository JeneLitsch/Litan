#pragma once
#include "Type.hxx"

namespace ltn::c::type {
	
	bool is_null(const Type & x);
	bool is_any(const Type & x);

	bool is_bool(const Type & x);
	bool is_char(const Type & x);
	bool is_int(const Type & x);
	bool is_float(const Type & x);

	bool is_integral(const Type & x);
	bool is_numeric(const Type & x);

	bool is_convertible(const Type & from, const Type & to);
}