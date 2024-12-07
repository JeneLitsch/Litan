#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>
#include <concepts>

namespace ltn::vm {
	class Type;
	struct Object;
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint16_t {
			NVLL = 0x00, TYPE,
			BOOL = 0x10, INT, FLOAT, CHAR,
			ARRAY = 0x20, STRING, TUPLE,
			ISTREAM = 0x30, OSTREAM,
			FUNCTION = 0x40, ITERATOR, ITERATOR_STOP, COROUTINE, NATIVE_FUNCTION,
			CLOCK = 0x50,
			STRUCT = 0x60,
			QUEUE = 0x70, MAP,
			RNG = 0x80, 

			FIRST_TYPE = ARRAY,
		};



		Type type;
		union {
			std::uint64_t u;
			std::int64_t i;
			stx::float64_t f;
			bool b;
			char c;
			const ltn::vm::Type * obj_type;
			ltn::vm::Object * object;
		};
	};
	namespace value {
		constexpr inline Value null {
			.type = Value::Type::NVLL,
			.b = false,
		};
		
		constexpr inline Value iterator_stop {
			.type = Value::Type::ITERATOR_STOP,
			.b = false,
		};

		constexpr inline Value boolean(bool b) {
			return Value{
				.type = Value::Type::BOOL,
				.b = b,
			};
		}

		constexpr inline Value integer(std::integral auto i) {
			return Value{
				.type = Value::Type::INT,
				.i = static_cast<std::int64_t>(i),
			};
		}

		constexpr inline Value floating(std::floating_point auto i) {
			return Value{
				.type = Value::Type::FLOAT,
				.f = static_cast<stx::float64_t>(i),
			};
		}

		constexpr inline Value character(auto i) {
			return Value{
				.type = Value::Type::CHAR,
				.c = static_cast<char>(i),
			};
		}

		constexpr inline Value string(Object * obj) {
			return Value{
				.type = Value::Type::STRING,
				.object = obj,
			};
		}

		constexpr inline Value array(Object * obj) {
			return Value{
				.type = Value::Type::ARRAY,
				.object = obj,
			};
		}

		constexpr inline Value queue(Object * obj) {
			return Value{
				.type = Value::Type::QUEUE,
				.object = obj,
			};
		}

		constexpr inline Value rng(Object * obj) {
			return Value{
				.type = Value::Type::RNG,
				.object = obj,
			};
		}

		constexpr inline Value tuple(Object * obj) {
			return Value{
				.type = Value::Type::TUPLE,
				.object = obj,
			};
		}

		constexpr inline Value iterator(Object * obj) {
			return Value{
				.type = Value::Type::ITERATOR,
				.object = obj,
			};
		}

		constexpr inline Value type(const Type * type) {
			return Value{
				.type = Value::Type::TYPE,
				.obj_type = type,
			};
		}

		constexpr inline Value map(Object * obj) {
			return Value{
				.type = Value::Type::MAP,
				.object = obj,
			};
		}

		constexpr inline Value clock(Object * obj) {
			return Value{
				.type = Value::Type::CLOCK,
				.object = obj,
			};
		}

		constexpr inline Value strukt(Object * obj) {
			return Value{
				.type = Value::Type::STRUCT,
				.object = obj,
			};
		}

		constexpr inline Value fx(Object * obj) {
			return Value{
				.type = Value::Type::FUNCTION,
				.object = obj,
			};
		}

		constexpr inline Value native_function(Object * obj) {
			return Value{
				.type = Value::Type::NATIVE_FUNCTION,
				.object = obj,
			};
		}

		constexpr inline Value coroutine(Object * obj) {
			return Value{
				.type = Value::Type::COROUTINE,
				.object = obj,
			};
		}

		constexpr inline Value ostream(Object * obj) {
			return Value{
				.type = Value::Type::OSTREAM,
				.object = obj,
			};
		}

		constexpr inline Value istream(Object * obj) {
			return Value{
				.type = Value::Type::ISTREAM,
				.object = obj,
			};
		}


		constexpr inline Value deduce(std::int64_t value) {
			return integer(value);
		}

		constexpr inline Value deduce(char value) {
			return character(value);
		} 
		
		constexpr inline Value deduce(stx::float64_t value) {
			return floating(value);
		}

		constexpr inline Value deduce(bool value) {
			return boolean(value);
		}

		template<typename T>
		T * as(const Value & value) {
			return static_cast<T*>(value.object);
		}
	}
}