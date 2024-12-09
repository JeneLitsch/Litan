#pragma once
#include "ltnvm/Value.hxx"
namespace ltn::vm {
	constexpr inline bool is_null(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::NVLL);
	}

	constexpr inline bool is_bool(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::BOOL);
	}

	constexpr inline bool is_char(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::CHAR);
	}

	constexpr inline bool is_int(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::INT);
	}

	constexpr inline bool is_float(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::FLOAT);
	}

	constexpr inline bool is_integral(const Value & val) {
		return is_bool(val) || is_char(val) || is_int(val);
	}

	constexpr inline bool is_numeric(const Value & val) {
		return is_integral(val) || is_float(val);
	}
	
	constexpr inline bool is_string(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::STRING);
	}

	constexpr inline bool is_array(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::ARRAY);
	}

	constexpr inline bool is_tuple(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::TUPLE);
	}

	constexpr inline bool is_ostream(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::OSTREAM);
	}

	constexpr inline bool is_istream(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::ISTREAM);
	}

	constexpr inline bool is_script_function(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::FUNCTION);
	}

	constexpr inline bool is_native_function(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::NATIVE_FUNCTION);
	}

	constexpr inline bool is_fxptr(const Value & val) {
		return is_script_function(val) || is_native_function(val);
	}

	constexpr inline bool is_clock(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::CLOCK);
	}

	constexpr inline bool is_struct(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::STRUCT);
	}

	constexpr inline bool is_stack(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::STACK);
	}

	constexpr inline bool is_queue(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::QUEUE);
	}

	constexpr inline bool is_map(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::MAP);
	}

	constexpr inline bool is_rng(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::RNG);
	}

	constexpr inline bool is_iterator(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::ITERATOR);
	}

	constexpr inline bool is_iterator_stop(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::ITERATOR_STOP);
	}

	constexpr inline bool is_type(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::TYPE);
	}


	constexpr inline bool is_contiguous(const Value & value) {
		return is_array(value) || is_tuple(value);
	}

	constexpr inline bool is_coroutine(const Value & val) {
		return val.type == static_cast<std::uint16_t>(ValueType::COROUTINE);
	}

	constexpr inline bool is_object(const Value & val) {
		return static_cast<std::uint64_t>(val.type) >= static_cast<std::uint64_t>(ValueType::FIRST_TYPE);
	}
}