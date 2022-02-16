#pragma once
#include <string_view>
#include <stdexcept>
#include "memory/Value.hxx"
#include "Exception.hxx"
namespace ltn::vm {
	template<class OP>
	constexpr inline Value calc(
		const Value & l,
		const Value & r) {
		constexpr OP op;
		if (isBool(l)) {
			if(isBool(r)) return Value{op(l.b, r.b)};
			if(isInt(r)) return Value{op(l.b, r.i)};
			if(isFloat(r)) return Value{op(l.b, r.f)};
		}
		if(isInt(l)) {
			if(isBool(r)) return Value{op(l.i, r.b)};
			if(isInt(r)) return Value{op(l.i, r.i)};
			if(isFloat(r)) return Value{op(l.i, r.f)};
		}
		if(isFloat(l)) {
			if(isBool(r)) return Value{op(l.f, r.b)};
			if(isInt(r)) return Value{op(l.f, r.i)};
			if(isFloat(r)) return Value{op(l.f, r.f)};
		}
		throw except::invalidOperands();
	}
}