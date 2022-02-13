#pragma once
#include <vector>
#include <cstdint>
#include <iterator>
#include <iostream>
#include "Value.hxx"

namespace ltn::vm {
	class Register {
	public:
		inline Value pop()  {
			const auto value = this->stack.back();
			this->stack.pop_back();
			return value;
		}

		inline void remove(std::uint64_t count)  {
			this->stack.resize(this->stack.size() - count);
		}

		inline void resize(std::uint64_t count)  {
			this->stack.resize(count);
		}

		inline const Value peek() const {
			return this->stack.back();
		}
		
		auto peek(std::uint64_t count) {
			auto begin = this->stack.end() - static_cast<std::int64_t>(count);
			auto end = this->stack.end();
			return std::make_pair(begin, end);
		}

		inline void push(const Value value) {
			this->stack.push_back(value);
		}

		void swap(std::uint64_t first, std::uint64_t second) {
			const auto size = this->size();
			const auto i1 = size - first - 1; 
			const auto i2 = size - second - 1; 
			std::swap(stack[i1], stack[i2]);
		}

		const std::vector<Value> & getContainer() const;

		void reset();
		std::size_t size() const;
	private:
		std::vector<Value> stack;
	};
}