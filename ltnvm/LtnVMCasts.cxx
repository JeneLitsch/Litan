#include "LtnVM.hxx"
#include "TypeCheck.hxx"
#include "cast.hxx"
#include <sstream>

namespace ltn::vm {
	void LtnVM::cast_int() {
		const auto value = this->reg.pop();
		const auto i = cast::to_int(value, this->heap);
		this->reg.push(Value(i));
	}


	void LtnVM::cast_float() {
		const auto value = this->reg.pop();
		const auto f = cast::to_float(value, this->heap);
		this->reg.push(Value(f));
	}


	void LtnVM::cast_string() {
		const auto value = this->reg.pop();
		const auto str = cast::to_string(value, this->heap);
		const auto ref = this->heap.alloc<String>(String{str});
		this->reg.push(Value{ref, Value::Type::STRING});
	}


	void LtnVM::cast_bool() {
		const auto value = this->reg.pop();
		const auto b = cast::to_bool(value);
		this->reg.push(Value(b));
	}
}