#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/memory/Value.hxx"
namespace ltn::vm {
	struct Array {
		constexpr static std::string_view typeName = "Array";
		
		std::vector<Value> arr;

		const auto & get() const {
			return this->arr;
		}
		
		auto & get() {
			return this->arr;
		}

		auto clone() const {
			return *this;
		}
	};
}