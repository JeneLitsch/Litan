#include "instructions.hxx"
#include "type_check.hxx"
#include "cast.hxx"
#include <sstream>

namespace ltn::vm::inst {
	void cast_char(VmCore & core) {
		const auto value = core.reg.pop();
		const auto c = cast::to_char(value);
		core.reg.push(value::character(c));
	}

	void cast_int(VmCore & core) {
		const auto value = core.reg.pop();
		const auto i = cast::to_int(value, core.heap);
		core.reg.push(value::integer(i));
	}


	void cast_float(VmCore & core) {
		const auto value = core.reg.pop();
		const auto f = cast::to_float(value, core.heap);
		core.reg.push(value::floating(f));
	}


	void cast_string(VmCore & core) {
		const auto value = core.reg.pop();
		if(is_string(value)) {
			core.reg.push(value);
		}
		else {
			const auto str = cast::to_string(value, core.heap);
			const auto ref = core.heap.alloc<String>(String{str});
			core.reg.push(Value{ref, Value::Type::STRING});
		}
	}


	void cast_bool(VmCore & core) {
		const auto value = core.reg.pop();
		const auto b = cast::to_bool(value);
		core.reg.push(Value(b));
	}


	void cast_array(VmCore & core) {
		const auto ref = core.reg.pop();
		
		if(is_array(ref)) {
			core.reg.push(ref);
			return;
		}

		if(is_range(ref)) {
			const auto & range = core.heap.read<Range>(ref.u);
			const auto arrRef = value::array(range.array);
			core.reg.push(arrRef);
			return;
		}

		auto && array = cast::to_array(ref);
		const auto ptr = core.heap.alloc<Array>({std::move(array)});
		const auto arrRef = value::array(ptr); 
		core.reg.push(arrRef);
	}
}