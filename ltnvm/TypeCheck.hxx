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

	constexpr inline bool isRange(const Value & val) {
		return val.type == Value::Type::RANGE;
	}

	constexpr inline bool isStack(const Value & val) {
		return val.type == Value::Type::STACK;
	}

	constexpr inline bool isQueue(const Value & val) {
		return val.type == Value::Type::QUEUE;
	}

	constexpr inline bool isMap(const Value & val) {
		return val.type == Value::Type::MAP;
	}



	constexpr inline bool isObject(const Value & val) {
		const auto first = static_cast<std::uint32_t>(Value::Type::OBJ_FIRST); 
		const auto last = static_cast<std::uint32_t>(Value::Type::OBJ_LAST);
		const auto value = static_cast<std::uint32_t>(val.type);
		return first <= value && value <= last;
	}
}