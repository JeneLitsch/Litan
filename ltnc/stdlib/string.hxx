#pragma once
inline const char * std_string = R"###(
namespace std {
	function split(string, delim) const 
		=> build_in(split_string)



	function join(strings, joiner) const
		=> std::reduce_l(strings, lambda[joiner](a,b) 
			=> std::str(a) + joiner + std::str(b)) ?? ""



	function replace(string, search_for, replace_with) const
		=> (search_for == "" && replace_with == "") 
			? string 
			: join(split(string, search_for), replace_with)



	function str(x) const
		=> build_in(to_string)

	
	
	function left_pad(str, min_size) {
		return " " * (min_size - std::size(str)) + str;
	}


	function right_pad(str, min_size) {
		return str + " " * (min_size - std::size(str));
	}
}
)###";
