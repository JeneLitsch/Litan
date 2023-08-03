#pragma once
#include "stdxx/float64_t.hxx"
#include <cstdint>
#include "ltnvm/objects/Object.hxx"

namespace ltn::vm {
	class Type;
	struct Value {
		// DO NOT TOUCH/CHANGE THE VALUES !!!
		enum class Type : std::uint16_t {
			NVLL = 0x00,
			BOOL = 0x10, INT, FLOAT, CHAR,
			ARRAY = 0x20, STRING, TUPLE,
			ISTREAM = 0x30, OSTREAM,
			FUNCTION = 0x40, ITERATOR, ITERATOR_STOP,
			CLOCK = 0x50,
			STRUCT = 0x60,
			QUEUE = 0x70, STACK, MAP,
			RNG = 0x80, TYPE,
		};

		constexpr Value()
			: type(Type::NVLL), u(0) {}

		constexpr Value(std::uint64_t value, Type type) 
			: type(type), u(value) {}

		constexpr Value(Object * object, Type type) 
			: type(type), object{object}{}
		
		constexpr Value(std::int64_t value) 
			: type(Type::INT), i(value) {}

		constexpr Value(char value) 
			: type(Type::CHAR), c(value) {}
		
		constexpr Value(stx::float64_t value)
			: type(Type::FLOAT), f(value) {}

		constexpr Value(bool value)
			: type(Type::BOOL), b(value) {}

		constexpr Value(const ltn::vm::Type * obj_type)
			: type(Type::TYPE), obj_type(obj_type) {}

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

		template<typename T>
		T * as() const {
			return static_cast<T*>(object);
		}
	};
	namespace value {
		constexpr inline Value null {std::uint64_t{0}, Value::Type::NVLL };
		constexpr inline Value iterator_stop {std::uint64_t{0}, Value::Type::ITERATOR_STOP };

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

		constexpr inline Value string(Object * obj) {
			return Value{obj, Value::Type::STRING};
		}

		constexpr inline Value array(Object * obj) {
			return Value{obj, Value::Type::ARRAY};
		}

		constexpr inline Value queue(Object * obj) {
			return Value{obj, Value::Type::QUEUE};
		}

		constexpr inline Value stack(Object * obj) {
			return Value{obj, Value::Type::STACK};
		}

		constexpr inline Value rng(Object * obj) {
			return Value{obj, Value::Type::RNG};
		}

		constexpr inline Value tuple(Object * obj) {
			return Value{obj, Value::Type::TUPLE};
		}

		constexpr inline Value iterator(Object * obj) {
			return Value{obj, Value::Type::ITERATOR};
		}

		constexpr inline Value type(const Type * type) {
			return Value{type};
		}

		constexpr inline Value fx(Object * obj) {
			return Value{obj, Value::Type::FUNCTION};
		}
	}
}