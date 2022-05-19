#pragma once
#include <iostream>
#include <string_view>
namespace ltn {
	inline const std::string_view version = "v3.0-pre0";
	bool print_version(auto arg) {
		if(std::string_view(arg) == std::string_view("--version")) {
			std::cout << "Litan: " << version << "\n"; 
			return true;
		}
		return false;
	}
}