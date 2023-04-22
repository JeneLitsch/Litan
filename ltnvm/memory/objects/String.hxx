#pragma once
#include <string>
#include <string_view>

namespace ltn::vm {
	struct String {
		std::string str;
		auto & get() { return str; }
		bool marked = false;
		bool in_use = false;
	};

	inline String clone(const String & string) {
		return string;
	}
}