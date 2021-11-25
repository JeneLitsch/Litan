#pragma once
#include "Value.hxx"
#include <string_view>
#include <stdexcept>
namespace ltn::vm {
	inline std::runtime_error typeError(
		const Value &,
		const Value &,
		const std::string_view & str) {
		return std::runtime_error{ static_cast<std::string>(str) };
	}

	template<class OP>
	constexpr inline  Value calc(
		const Value & l,
		const Value & r,
		const std::string_view & msg) {
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
		throw typeError(l, r, msg);
	}
}