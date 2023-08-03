#pragma once
#include <vector>
#include <string_view>
#include "ltnvm/Value.hxx"
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	struct Contiguous : public Object {
	protected:
		Contiguous(std::vector<Value> data = {}) : data {data} {}

	public:
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
}