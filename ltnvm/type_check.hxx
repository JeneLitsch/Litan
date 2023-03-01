#pragma once
#include "memory/Value.hxx"
namespace ltn::vm {
	constexpr inline bool is_null(const Value & val) {
		return val.type == Value::Type::NVLL;
	}

	constexpr inline bool is_bool(const Value & val) {
		return val.type == Value::Type::BOOL;
	}

	constexpr inline bool is_char(const Value & val) {
		return val.type == Value::Type::CHAR;
	}

	constexpr inline bool is_int(const Value & val) {
		return val.type == Value::Type::INT;
	}

	constexpr inline bool is_float(const Value & val) {
		return val.type == Value::Type::FLOAT;
	}

	constexpr inline bool is_integral(const Value & val) {
		return is_bool(val) || is_char(val) || is_int(val);
	}

	constexpr inline bool is_numeric(const Value & val) {
		return is_integral(val) || is_float(val);
	}
	
	constexpr inline bool is_string(const Value & val) {
		return val.type == Value::Type::STRING;
	}

	constexpr inline bool is_array(const Value & val) {
		return val.type == Value::Type::ARRAY;
	}

	constexpr inline bool is_tuple(const Value & val) {
		return val.type == Value::Type::TUPLE;
	}

	constexpr inline bool is_ostream(const Value & val) {
		return val.type == Value::Type::OSTREAM;
	}

	constexpr inline bool is_istream(const Value & val) {
		return val.type == Value::Type::ISTREAM;
	}

	constexpr inline bool is_fxptr(const Value & val) {
		return val.type == Value::Type::FX_PTR;
	}

	constexpr inline bool is_external(const Value & val) {
		return val.type == Value::Type::EXTERNAL;
	}

	constexpr inline bool is_clock(const Value & val) {
		return val.type == Value::Type::CLOCK;
	}

	constexpr inline bool is_struct(const Value & val) {
		return val.type == Value::Type::STRUCT;
	}

	constexpr inline bool is_stack(const Value & val) {
		return val.type == Value::Type::STACK;
	}

	constexpr inline bool is_queue(const Value & val) {
		return val.type == Value::Type::QUEUE;
	}

	constexpr inline bool is_map(const Value & val) {
		return val.type == Value::Type::MAP;
	}

	constexpr inline bool is_rng(const Value & val) {
		return val.type == Value::Type::RNG;
	}
}