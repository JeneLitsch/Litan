#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>
#include <array>

namespace ltn::vm {
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint32_t {
			NVLL = 0x00,
			BOOL = 0x10, INT, FLOAT, CHAR,
			ARRAY = 0x20, STRING, TUPLE,
			ISTREAM = 0x30, OSTREAM,
			FX_PTR = 0x40, 
			CLOCK = 0x50,
			STRUCT = 0x60,
			QUEUE = 0x70, STACK, MAP,
			RNG = 0x80,
		};

		constexpr Value()
			: type(Type::NVLL), ptr(0) {}

		constexpr Value(void * ptr, Type type) 
			: type(type), ptr(ptr) {}

		constexpr Value(std::int64_t value) 
			: type(Type::INT), i(value) {}

		constexpr Value(char value) 
			: type(Type::CHAR), c(value) {}
		
		constexpr Value(stx::float64_t value)
			: type(Type::FLOAT), f(value) {}

		constexpr Value(bool value)
			: type(Type::BOOL), b(value) {}

		Type type;
		union {
			std::uint64_t u;
			std::int64_t i;
			stx::float64_t f;
			bool b;
			char c;
			void * ptr;
		};
	};
	namespace value {
		constexpr inline Value null;

		constexpr inline Value boolean(bool b) {
			return Value{b};
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

		constexpr inline Value string(void * ptr) {
			return Value{ptr, Value::Type::STRING};
		}

		constexpr inline Value array(void * ptr) {
			return Value{ptr, Value::Type::ARRAY};
		}

		constexpr inline Value rng(void * ptr) {
			return Value{ptr, Value::Type::RNG};
		}

		constexpr inline Value tuple(void * ptr) {
			return Value{ptr, Value::Type::TUPLE};
		}
	}
}