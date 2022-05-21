#include "instructions.hxx"
#include "type_check.hxx"
#include <iostream>
#include <string>

namespace ltn::vm::inst {
	void newi(VmCore & core){
		core.reg.push(Value{core.fetch_uint(), Value::Type::INT});
	}


	void newf(VmCore & core){
		core.reg.push(Value{core.fetch_uint(), Value::Type::FLOAT});
	}


	void newu(VmCore & core){
		core.reg.push(Value{core.fetch_uint(), Value::Type::NVLL});
	}
	

	void newc(VmCore & core) {
		const auto chr = core.fetch_byte();
		core.reg.push(value::character(chr));
	}
	

	void truE(VmCore & core){
		core.reg.push(Value{true, Value::Type::BOOL});
	}


	void falsE(VmCore & core){
		core.reg.push(Value{false, Value::Type::BOOL});
	}


	void null(VmCore & core) {
		core.reg.push(Value{false, Value::Type::NVLL});
	}
}