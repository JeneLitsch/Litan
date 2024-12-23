#pragma once
#include <string_view>
#include <stdexcept>
#include "ltnvm/Value.hxx"
#include "ltnvm/Exception.hxx"
namespace ltn::vm {
	template<typename Op>
	constexpr inline Value calc_r(
		auto l,
		const Value & r) {
		constexpr Op op;
		if(is_bool(r))  return value::deduce(op(l, r.b));
		if(is_int(r))   return value::deduce(op(l, r.i));
		if(is_float(r)) return value::deduce(op(l, r.f));
		throw except::invalid_operands();
	}

	template<typename Op>
	constexpr inline Value calc(
		const Value & l,
		const Value & r) {
		if (is_bool(l))  return calc_r<Op>(l.b, r);
		if (is_int(l))   return calc_r<Op>(l.i, r);
		if (is_float(l)) return calc_r<Op>(l.f, r);
		throw except::invalid_operands();
	}
}