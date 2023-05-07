#pragma once

namespace ltn::vm {
	template<typename Op, typename ... Args>
	auto decode_type(const std::uint8_t * code, Args && ...args) {
		switch (*code) {
			case type_code::ANY: return Op::for_any(code, args...);
			case type_code::NVLL: return Op::for_null(code, args...);
			case type_code::BOOL: return Op::for_bool(code, args...);
			case type_code::CHAR: return Op::for_char(code, args...);
			case type_code::INT: return Op::for_int(code, args...);
			case type_code::FLOAT: return Op::for_float(code, args...);
			case type_code::STRING: return Op::for_string(code, args...);
			case type_code::ARRAY: return Op::for_array(code, args...);
			case type_code::TUPLE: return Op::for_tuple(code, args...);
			case type_code::TUPLE_N: return Op::for_tuple_n(code, args...);
			case type_code::FX: return Op::for_fx(code, args...);
			case type_code::FX_N: return Op::for_fx_n(code, args...);
			case type_code::ISTREAM: return Op::for_istream(code, args...);
			case type_code::OSTREAM: return Op::for_ostream(code, args...);
			case type_code::ITERATOR: return Op::for_iter(code, args...);
			case type_code::ITERATOR_STOP: return Op::for_stop(code, args...);
			case type_code::RNG: return Op::for_rng(code, args...);
			case type_code::CLOCK: return Op::for_clock(code, args...);
			case type_code::TYPE: return Op::for_type(code, args...);
			case type_code::QUEUE: return Op::for_queue(code, args...);
			case type_code::STACK: return Op::for_stack(code, args...);
			case type_code::MAP: return Op::for_map(code, args...);
			default: return Op::for_default(code, args...);
		}
	}


	inline std::uint64_t size_uint_8(const std::uint8_t *& code) {
		std::uint64_t size = 0;
		for(std::size_t i = 0; i < 8; ++i) {
			size += static_cast<std::uint64_t>(*(++code)) << (i * 8);
		}
		return size;
	}
	
	inline void decode_tuple(const std::uint8_t * code, auto fx) {
		auto size = size_uint_8(code);
		for(std::size_t i = 0; i < size; ++i) {
			fx(++code);
		}
	}
}