#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>
#include <concepts>
#include "native/Value.h"

namespace ltn::vm {
	class Type;
	struct Object;
	using ValueType = ltn_ValueType;
	using Value = ltn_Value;

	namespace value {
		constexpr inline Value null {
			.type = ValueType::NVLL,
			.b = false,
		};
		
		constexpr inline Value iterator_stop {
			.type = ValueType::ITERATOR_STOP,
			.b = false,
		};

		constexpr inline Value boolean(bool b) {
			return Value{
				.type = ValueType::BOOL,
				.b = b,
			};
		}

		constexpr inline Value integer(std::integral auto i) {
			return Value{
				.type = ValueType::INT,
				.i = static_cast<std::int64_t>(i),
			};
		}

		constexpr inline Value floating(std::floating_point auto i) {
			return Value{
				.type = ValueType::FLOAT,
				.f = static_cast<stx::float64_t>(i),
			};
		}

		constexpr inline Value character(auto i) {
			return Value{
				.type = ValueType::CHAR,
				.c = static_cast<char>(i),
			};
		}

		constexpr inline Value string(Object * obj) {
			return Value{
				.type = ValueType::STRING,
				.object = obj,
			};
		}

		constexpr inline Value array(Object * obj) {
			return Value{
				.type = ValueType::ARRAY,
				.object = obj,
			};
		}

		constexpr inline Value queue(Object * obj) {
			return Value{
				.type = ValueType::QUEUE,
				.object = obj,
			};
		}

		constexpr inline Value rng(Object * obj) {
			return Value{
				.type = ValueType::RNG,
				.object = obj,
			};
		}

		constexpr inline Value tuple(Object * obj) {
			return Value{
				.type = ValueType::TUPLE,
				.object = obj,
			};
		}

		constexpr inline Value iterator(Object * obj) {
			return Value{
				.type = ValueType::ITERATOR,
				.object = obj,
			};
		}

		constexpr inline Value type(const Type * type) {
			return Value{
				.type = ValueType::TYPE,
				.obj_type = static_cast<const ltn_TypePtr>(type),
			};
		}

		constexpr inline Value map(Object * obj) {
			return Value{
				.type = ValueType::MAP,
				.object = obj,
			};
		}

		constexpr inline Value clock(Object * obj) {
			return Value{
				.type = ValueType::CLOCK,
				.object = obj,
			};
		}

		constexpr inline Value strukt(Object * obj) {
			return Value{
				.type = ValueType::STRUCT,
				.object = obj,
			};
		}

		constexpr inline Value fx(Object * obj) {
			return Value{
				.type = ValueType::FUNCTION,
				.object = obj,
			};
		}

		constexpr inline Value native_function(Object * obj) {
			return Value{
				.type = ValueType::NATIVE_FUNCTION,
				.object = obj,
			};
		}

		constexpr inline Value coroutine(Object * obj) {
			return Value{
				.type = ValueType::COROUTINE,
				.object = obj,
			};
		}

		constexpr inline Value ostream(Object * obj) {
			return Value{
				.type = ValueType::OSTREAM,
				.object = obj,
			};
		}

		constexpr inline Value istream(Object * obj) {
			return Value{
				.type = ValueType::ISTREAM,
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

		constexpr inline const Type * as_type_object(const Value & value) {
			return static_cast<const Type*>(value.obj_type);
		}
	}
}