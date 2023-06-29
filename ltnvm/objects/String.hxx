#pragma once
#include <string>
#include <string_view>
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct String : public Object {
		String(std::string data) : data {data} {}
		std::string data;
	};


	inline String clone(const String & string) {
		return string;
	}
}