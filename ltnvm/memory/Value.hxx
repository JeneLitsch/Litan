#pragma once
#include <cstdint>

namespace ltn::vm {
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint32_t {
			NVLL = 0x00, ADDR,
			BOOL = 0x10, INT, FLOAT, 
			ARRAY = 0x20, STRING,
			ISTREAM = 0x30, OSTREAM,
			FX_PTR = 0x40, EXTERNAL,
			CLOCK = 0x50,
			STRUCT = 0x60, RANGE,
			QUEUE = 0x70, STACK, MAP,
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
	namespace value {
		constexpr inline Value null {0, Value::Type::NVLL };
		constexpr inline Value integer(auto i) {
			return Value{static_cast<std::int64_t>(i)};
		}
	}

}