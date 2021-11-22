#include "Value.hxx"
namespace ltn::vm {
	inline bool isInt(const Value & val) {
		return val.type == Value::Type::INT;
	}

	inline bool isFloat(const Value & val) {
		return val.type == Value::Type::FLOAT;
	}

	inline bool isBool(const Value & val) {
		return val.type == Value::Type::BOOL;
	}

	inline bool isAddr(const Value & val) {
		return val.type == Value::Type::ADDR;
	}

	inline bool isStr(const Value & val) {
		return val.type == Value::Type::STRING;
	}

	inline bool isArr(const Value & val) {
		return val.type == Value::Type::ARRAY;
	}
}