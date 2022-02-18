#pragma once
#include <string_view>
#include <stdexcept>
#include "memory/Value.hxx"
#include "Exception.hxx"
namespace ltn::vm {
	template<typename Op>
	constexpr inline Value calcR(
		auto l,
		const Value & r) {
		constexpr Op op;
		if(isBool(r))  return Value{op(l, r.b)};
		if(isInt(r))   return Value{op(l, r.i)};
		if(isFloat(r)) return Value{op(l, r.f)};
		if(isChar(r))  return Value{op(l, r.c)};
		throw except::invalidOperands();
	}

	template<typename Op>
	constexpr inline Value calc(
		const Value & l,
		const Value & r) {
		if (isBool(l))  return calcR<Op>(l.b, r);
		if (isInt(l))   return calcR<Op>(l.i, r);
		if (isFloat(l)) return calcR<Op>(l.f, r);
		if (isChar(l))  return calcR<Op>(l.c, r);
		throw except::invalidOperands();
	}
}