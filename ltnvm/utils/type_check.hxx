#pragma once
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	constexpr inline bool is_null(const Value & val) {
		return val.type == ValueType::NVLL;
	}

	constexpr inline bool is_bool(const Value & val) {
		return val.type == ValueType::BOOL;
	}

	constexpr inline bool is_char(const Value & val) {
		return val.type == ValueType::CHAR;
	}

	constexpr inline bool is_int(const Value & val) {
		return val.type == ValueType::INT;
	}

	constexpr inline bool is_float(const Value & val) {
		return val.type == ValueType::FLOAT;
	}

	constexpr inline bool is_integral(const Value & val) {
		return is_bool(val) || is_char(val) || is_int(val);
	}

	constexpr inline bool is_numeric(const Value & val) {
		return is_integral(val) || is_float(val);
	}
	
	constexpr inline bool is_string(const Value & val) {
		return val.type == ValueType::STRING;
	}

	constexpr inline bool is_array(const Value & val) {
		return val.type == ValueType::ARRAY;
	}

	constexpr inline bool is_tuple(const Value & val) {
		return val.type == ValueType::TUPLE;
	}

	constexpr inline bool is_ostream(const Value & val) {
		return val.type == ValueType::OSTREAM;
	}

	constexpr inline bool is_istream(const Value & val) {
		return val.type == ValueType::ISTREAM;
	}

	constexpr inline bool is_script_function(const Value & val) {
		return val.type == ValueType::FUNCTION;
	}

	constexpr inline bool is_native_function(const Value & val) {
		return val.type == ValueType::NATIVE_FUNCTION;
	}

	constexpr inline bool is_fxptr(const Value & val) {
		return is_script_function(val) || is_native_function(val);
	}

	constexpr inline bool is_clock(const Value & val) {
		return val.type == ValueType::CLOCK;
	}

	constexpr inline bool is_struct(const Value & val) {
		return val.type == ValueType::STRUCT;
	}

	constexpr inline bool is_queue(const Value & val) {
		return val.type == ValueType::QUEUE;
	}

	constexpr inline bool is_map(const Value & val) {
		return val.type == ValueType::MAP;
	}

	constexpr inline bool is_rng(const Value & val) {
		return val.type == ValueType::RNG;
	}

	constexpr inline bool is_iterator(const Value & val) {
		return val.type == ValueType::ITERATOR;
	}

	constexpr inline bool is_iterator_stop(const Value & val) {
		return val.type == ValueType::ITERATOR_STOP;
	}

	constexpr inline bool is_type(const Value & val) {
		return val.type == ValueType::TYPE;
	}


	constexpr inline bool is_contiguous(const Value & value) {
		return is_array(value) || is_tuple(value);
	}

	constexpr inline bool is_coroutine(const Value & val) {
		return val.type == ValueType::COROUTINE;
	}

	constexpr inline bool is_object(const Value & val) {
		return static_cast<std::uint64_t>(val.type) >= static_cast<std::uint64_t>(ValueType::FIRST_TYPE);
	}
}