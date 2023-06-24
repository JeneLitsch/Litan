#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	struct Array {
		std::vector<Value> data;

		inline void push_back(const Value & value) {
			data.push_back(value);
		}

		inline bool empty() const {
			return std::empty(data);
		}

		auto begin() { return std::begin(data); }
		auto end() { return std::end(data); }

		auto begin() const { return std::begin(data); }
		auto end() const { return std::end(data); }

		auto cbegin() const { return std::cbegin(data); }
		auto cend() const { return std::cend(data); }
	};

	inline Array clone(const Array & arr) {
		return arr;
	}
}