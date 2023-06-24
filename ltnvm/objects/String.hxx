#pragma once
#include <string>
#include <string_view>

namespace ltn::vm {
	struct String {
		std::string data;
	};


	inline String clone(const String & string) {
		return string;
	}
}