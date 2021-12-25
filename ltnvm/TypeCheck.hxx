#pragma once
#include "memory/Value.hxx"
namespace ltn::vm {
	constexpr inline bool isNull(const Value & val) {
		return val.type == Value::Type::NVLL;
	}

	constexpr inline bool isInt(const Value & val) {
		return val.type == Value::Type::INT;
	}

	constexpr inline bool isFloat(const Value & val) {
		return val.type == Value::Type::FLOAT;
	}

	constexpr inline bool isBool(const Value & val) {
		return val.type == Value::Type::BOOL;
	}

	constexpr inline bool isAddr(const Value & val) {
		return val.type == Value::Type::ADDR;
	}

	constexpr inline bool isStr(const Value & val) {
		return val.type == Value::Type::STRING;
	}

	constexpr inline bool isArr(const Value & val) {
		return val.type == Value::Type::ARRAY;
	}

	constexpr inline bool isOStream(const Value & val) {
		return val.type == Value::Type::OSTREAM;
	}

	constexpr inline bool isIStream(const Value & val) {
		return val.type == Value::Type::ISTREAM;
	}

	constexpr inline bool isFxPtr(const Value & val) {
		return val.type == Value::Type::FX_PTR;
	}

	constexpr inline bool isExt(const Value & val) {
		return val.type == Value::Type::EXTERNAL;
	}

	constexpr inline bool isClock(const Value & val) {
		return val.type == Value::Type::CLOCK;
	}

	constexpr inline bool isStruct(const Value & val) {
		return val.type == Value::Type::STRUCT;
	}
}