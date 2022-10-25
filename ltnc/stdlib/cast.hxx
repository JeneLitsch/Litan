#pragma once
inline const char * std_cast = R"###(
namespace std {
	build_in bool(x) const   @ cast_bool
	build_in char(x) const   @ cast_char
	build_in int(x) const    @ cast_int
	build_in float(x) const  @ cast_float
	build_in string(x) const @ cast_string

	build_in to_string(x) const @ to_string
	build_in str(x) const @ to_string
}
)###";
