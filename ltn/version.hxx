#pragma once
#include <iostream>
#include <string_view>
namespace ltn {
	inline const std::string_view version = "v3.0-pre";
	bool print_version(auto arg) {
		if(std::string_view(arg) == std::string_view("--version")) {
			std::cout << "Litan: " << version << "\n"; 
			return true;
		}
		return false;
	}


	inline constexpr std::uint8_t major_version = 3;

	inline bool is_compatible(std::uint8_t version) {
		return version == major_version;
	}
}