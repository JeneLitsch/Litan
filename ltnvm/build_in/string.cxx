#include "string.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/stringify.hxx"

namespace ltn::vm::build_in {


	Value to_string(VmCore & core) {
		const auto input = core.reg.pop();
		const auto addr = core.heap.alloc<String>({stringify(input, core.heap)});
		return value::string(addr);
	}



	Value parse_bool(VmCore & core) {
		return value::null;
	}



	Value parse_char(VmCore & core) {
		return value::null;
	}



	Value parse_int(VmCore & core) {
		return value::null;
	}



	Value parse_float(VmCore & core) {
		return value::null;
	}	
}