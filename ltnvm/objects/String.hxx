#pragma once
#include <string>
#include <string_view>

namespace ltn::vm {
	using String = std::string;

	inline String clone(const String & string) {
		return string;
	}
}