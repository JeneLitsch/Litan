#pragma once
#include <vector>
#include <cstdint>
#include "Value.hxx"

namespace ltn::vm {
	class Register {
	public:
		inline Value pop()  {
			const auto value = this->stack.back();
			this->stack.pop_back();
			return value;
		}

		inline const Value peek() const {
			return this->stack.back();
		}
		
		inline void push(const Value value) {
			this->stack.push_back(value);
		}

		const std::vector<Value> & getContainer() const;

		void reset();
		std::size_t size() const;
	private:
		std::vector<Value> stack;
	};
}