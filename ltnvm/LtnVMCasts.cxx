#include "LtnVM.hxx"
#include "type_check.hxx"
#include "cast.hxx"
#include <sstream>

namespace ltn::vm {
	void LtnVM::cast_char() {
		const auto value = this->core.reg.pop();
		const auto c = cast::to_char(value);
		this->core.reg.push(value::character(c));
	}

	void LtnVM::cast_int() {
		const auto value = this->core.reg.pop();
		const auto i = cast::to_int(value, this->core.heap);
		this->core.reg.push(value::integer(i));
	}


	void LtnVM::cast_float() {
		const auto value = this->core.reg.pop();
		const auto f = cast::to_float(value, this->core.heap);
		this->core.reg.push(value::floating(f));
	}


	void LtnVM::cast_string() {
		const auto value = this->core.reg.pop();
		if(is_string(value)) {
			this->core.reg.push(value);
		}
		else {
			const auto str = cast::to_string(value, this->core.heap);
			const auto ref = this->core.heap.alloc<String>(String{str});
			this->core.reg.push(Value{ref, Value::Type::STRING});
		}
	}


	void LtnVM::cast_bool() {
		const auto value = this->core.reg.pop();
		const auto b = cast::to_bool(value);
		this->core.reg.push(Value(b));
	}


	void LtnVM::cast_array() {
		const auto ref = this->core.reg.pop();
		
		if(is_array(ref)) {
			this->core.reg.push(ref);
			return;
		}

		if(is_range(ref)) {
			const auto & range = this->core.heap.read<Range>(ref.u);
			const auto arrRef = value::array(range.array);
			this->core.reg.push(arrRef);
			return;
		}

		auto && array = cast::to_array(ref);
		const auto ptr = this->core.heap.alloc<Array>({std::move(array)});
		const auto arrRef = value::array(ptr); 
		this->core.reg.push(arrRef);
	}
}