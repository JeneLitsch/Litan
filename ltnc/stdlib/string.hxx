#pragma once
inline const char * std_string = R"###(
namespace std {
	build_in split(string : string, delim : string) const -> array<string>
		@split_string

	build_in join(strings : array<string>, joiner : string) const -> string
		@join_string

	function replace(
		string: string,
		search_for: string,
		replace_with: string) const -> string
		=> (search_for == "" && replace_with == "") ?  string : join(split(string, search_for), replace_with)

	build_in str(x : any) const -> string
		@ to_string
}
)###";
