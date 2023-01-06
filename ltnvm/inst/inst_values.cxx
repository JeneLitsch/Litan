#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include <iostream>
#include <string>
#include "stdxx/casting.hxx"

namespace ltn::vm::inst {
	void newi(VmCore & core){
		core.reg.push(Value{core.fetch_uint(), Value::Type::INT});
	}



	void newf(VmCore & core){
		const std::uint64_t raw = core.fetch_uint();
		core.reg.push(value::floating(stx::bitcast<stx::float64_t>(raw)));
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