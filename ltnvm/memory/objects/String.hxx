#pragma once
#include <string>
#include <string_view>

namespace ltn::vm {
	struct String {
		std::string str;
		constexpr static std::string_view typeName = "String";
		const std::string & get() const {
			return this->str;
		}
		std::string & get() {
			return this->str;
		}
	};
}