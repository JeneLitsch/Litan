#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>

namespace ltn::vm {
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint32_t {
			NVLL = 0x00,
			BOOL = 0x10, INT, FLOAT, CHAR,
			ARRAY = 0x20, STRING, TUPLE,
			ISTREAM = 0x30, OSTREAM,
			FX_PTR = 0x40, ITERATOR, ITERATOR_STOP,
			CLOCK = 0x50,
			STRUCT = 0x60,
			QUEUE = 0x70, STACK, MAP,
			RNG = 0x80, TYPE,
		};

		constexpr Value()
			: type(Type::NVLL), u(0) {}

		constexpr Value(std::uint64_t value, Type type) 
			: type(type), u(value) {}
		
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
		};
	};
	namespace value {
		constexpr inline Value null {0, Value::Type::NVLL };
		constexpr inline Value iterator_stop {0, Value::Type::ITERATOR_STOP };

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

		constexpr inline Value string(std::uint64_t address) {
			return Value{address, Value::Type::STRING};
		}

		constexpr inline Value array(std::uint64_t address) {
			return Value{address, Value::Type::ARRAY};
		}

		constexpr inline Value rng(std::uint64_t address) {
			return Value{address, Value::Type::RNG};
		}

		constexpr inline Value tuple(std::uint64_t address) {
			return Value{address, Value::Type::TUPLE};
		}

		constexpr inline Value iterator(std::uint64_t address) {
			return Value{address, Value::Type::ITERATOR};
		}

		constexpr inline Value type(std::uint64_t address) {
			return Value{address, Value::Type::TYPE};
		}

		constexpr inline Value fx(std::uint64_t address) {
			return Value{address, Value::Type::FX_PTR};
		}
	}
}