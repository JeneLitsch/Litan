#pragma once
#include <cstdint>

namespace ltn::vm {
	struct Value {
		enum class Type : std::uint32_t {
			NVLL, ADDR,
			INT, FLOAT, BOOL,
			ARRAY, STRING,
		};
		constexpr Value()
			: u(0), type(Type::NVLL) {}

		constexpr Value(std::uint64_t value, Type type) 
			: u(value), type(type) {}
		
		constexpr Value(std::int64_t value) 
			: i(value), type(Type::INT) {}
		
		constexpr Value(double value)
			: f(value), type(Type::FLOAT) {}

		constexpr Value(bool value)
			: b(value), type(Type::BOOL) {}

		union {
			std::uint64_t u;
			std::int64_t i;
			double f;
			bool b;
		};
		Type type;
	};	
}