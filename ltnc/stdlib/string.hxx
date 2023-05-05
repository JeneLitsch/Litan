#pragma once
inline const char * std_string = R"###(
namespace std {
	build_in split(string, delim) const 
		@split_string

	build_in join(strings, joiner) const
		@join_string

	function replace(string, search_for, replace_with) const
		=> (search_for == "" && replace_with == "") 
			? string 
			: join(split(string, search_for), replace_with)

	build_in str(x) const @ to_string
}
)###";
