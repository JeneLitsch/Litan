#pragma once
inline const char * std_json = R"###(
namespace std::json {
	function parse(string) const => build_in(json_parse)
	function print(json)   const => build_in(json_print)
} 
)###";
