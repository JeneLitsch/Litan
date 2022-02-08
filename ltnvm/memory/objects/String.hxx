#pragma once
#include <string>
#include <string_view>

namespace ltn::vm {
	struct String {
		constexpr static std::string_view typeName = "String";
		
		std::string str;
		
		auto & get() {
			return this->str;
		}

		const auto & get() const {
			return this->str;
		}

		auto clone() const {
			return *this;
		}
	};
}