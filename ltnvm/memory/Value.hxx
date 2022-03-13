#pragma once
#include "ltn/float64_t.hxx"
#include <cstdint>

namespace ltn::vm {
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint32_t {
			NVLL = 0x00, ADDR,
			BOOL = 0x10, INT, FLOAT, CHAR,
			ARRAY = 0x20, STRING,
			ISTREAM = 0x30, OSTREAM,
			FX_PTR = 0x40, EXTERNAL,
			CLOCK = 0x50,
			STRUCT = 0x60, RANGE,
			QUEUE = 0x70, STACK, MAP,
			RNG = 0x80,

			OBJ_FIRST = ARRAY,
			OBJ_LAST = RNG,
		};
		constexpr Value()
			: u(0), type(Type::NVLL) {}

		constexpr Value(std::uint64_t value, Type type) 
			: u(value), type(type) {}
		
		constexpr Value(std::int64_t value) 
			: i(value), type(Type::INT) {}

		constexpr Value(char value) 
			: c(value), type(Type::CHAR) {}
		
		constexpr Value(stx::float64_t value)
			: f(value), type(Type::FLOAT) {}

		constexpr Value(bool value)
			: b(value), type(Type::BOOL) {}

		union {
			std::uint64_t u;
			std::int64_t i;
			stx::float64_t f;
			bool b;
			char c;
		};
		Type type;
	};
	namespace value {
		constexpr inline Value null {0, Value::Type::NVLL };

		constexpr inline Value boolean(bool b) {
			return Value{b, Value::Type::BOOL};
		}

		constexpr inline Value integer(auto i) {
			return Value{static_cast<std::int64_t>(i)};
		}

		constexpr inline Value floating(auto i) {
			return Value{static_cast<stx::float64_t>(i)};
		}

		constexpr inline Value character(auto i) {
			return Value{static_cast<char>(i)};
		}

		constexpr inline Value string(std::uint64_t addr) {
			return Value{addr, Value::Type::STRING};
		}

		constexpr inline Value array(std::uint64_t addr) {
			return Value{addr, Value::Type::ARRAY};
		}

		constexpr inline Value rng(std::uint64_t addr) {
			return Value{addr, Value::Type::RNG};
		}
	}
}