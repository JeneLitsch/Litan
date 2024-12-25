#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>
#include <concepts>

#include "native/Value.h"

namespace ltn::vm {
	class Type;
	struct Object;


	enum class ValueType {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		NVLL = 0x00,
		ITERATOR_STOP,
		TYPE,
		
		BOOL = 0x10,
		INT, 
		FLOAT,
		
		ARRAY = 0x20, 
		STRING,
		TUPLE,
		
		ISTREAM = 0x30,
		OSTREAM,
		
		FUNCTION = 0x40,
		ITERATOR,
		COROUTINE,
		NATIVE_FUNCTION,
		
		CLOCK = 0x50,
		
		STRUCT = 0x60,
		
		QUEUE = 0x70,
		STACK,
		MAP,
		
		RNG = 0x80, 

		FIRST_TYPE = ARRAY
	};
	
	using Value = ltn_Value;

	namespace value {
		constexpr inline Value null {
			.type = static_cast<std::uint16_t>(ValueType::NVLL),
			.b = false,
		};
		
		constexpr inline Value iterator_stop {
			.type = static_cast<std::uint16_t>(ValueType::ITERATOR_STOP),
			.b = false,
		};

		constexpr inline Value boolean(bool b) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::BOOL),
				.b = b,
			};
		}

		constexpr inline Value integer(std::integral auto i) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::INT),
				.i = static_cast<std::int64_t>(i),
			};
		}

		constexpr inline Value floating(std::floating_point auto i) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::FLOAT),
				.f = static_cast<stx::float64_t>(i),
			};
		}

		constexpr inline Value string(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::STRING),
				.object = obj,
			};
		}

		constexpr inline Value array(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::ARRAY),
				.object = obj,
			};
		}

		constexpr inline Value queue(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::QUEUE),
				.object = obj,
			};
		}

		constexpr inline Value stack(Object * obj) {
				return Value{
				.type = static_cast<std::uint16_t>(ValueType::STACK),
				.object = obj,
			};
		}

		constexpr inline Value rng(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::RNG),
				.object = obj,
			};
		}

		constexpr inline Value tuple(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::TUPLE),
				.object = obj,
			};
		}

		constexpr inline Value iterator(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::ITERATOR),
				.object = obj,
			};
		}

		constexpr inline Value type(const Type * type) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::TYPE),
				.obj_type = static_cast<ltn_TypePtr>(type),
			};
		}

		constexpr inline Value map(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::MAP),
				.object = obj,
			};
		}

		constexpr inline Value clock(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::CLOCK),
				.object = obj,
			};
		}

		constexpr inline Value strukt(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::STRUCT),
				.object = obj,
			};
		}

		constexpr inline Value fx(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::FUNCTION),
				.object = obj,
			};
		}

		constexpr inline Value native_function(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::NATIVE_FUNCTION),
				.object = obj,
			};
		}

		constexpr inline Value coroutine(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::COROUTINE),
				.object = obj,
			};
		}

		constexpr inline Value ostream(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::OSTREAM),
				.object = obj,
			};
		}

		constexpr inline Value istream(Object * obj) {
			return Value{
				.type = static_cast<std::uint16_t>(ValueType::ISTREAM),
				.object = obj,
			};
		}


		constexpr inline Value deduce(std::int64_t value) {
			return integer(value);
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