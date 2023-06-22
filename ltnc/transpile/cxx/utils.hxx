#pragma once
#include <string>
#include <algorithm>
#include <string_view>

namespace ltn::c::trans {
	std::string to_lowercase(std::string_view in);
	std::string to_uppercase(std::string_view in);
	std::string to_capitalized(std::string_view in);
}