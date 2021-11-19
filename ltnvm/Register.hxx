#pragma once
#include <vector>
#include <cstdint>
#include "Value.hxx"

namespace ltn::vm {
	class Register {
	public:
		Value pop();
		void push(Value value);
	private:
		std::vector<Value> stack;
	};
}