#pragma once
#include <string_view>
#include <stdexcept>
#include "memory/Value.hxx"
#include "Exception.hxx"
namespace ltn::vm {
	template<typename Op>
	constexpr inline Value calc_r(
		auto l,
		const Value & r) {
		constexpr Op op;
		if(is_bool(r))  return Value{op(l, r.b)};
		if(is_int(r))   return Value{op(l, r.i)};
		if(is_float(r)) return Value{op(l, r.f)};
		if(is_char(r))  return Value{op(l, r.c)};
		throw except::invalid_operands();
	}

	template<typename Op>
	constexpr inline Value calc(
		const Value & l,
		const Value & r) {
		if (is_bool(l))  return calc_r<Op>(l.b, r);
		if (is_int(l))   return calc_r<Op>(l.i, r);
		if (is_float(l)) return calc_r<Op>(l.f, r);
		if (is_char(l))  return calc_r<Op>(l.c, r);
		throw except::invalid_operands();
	}
}