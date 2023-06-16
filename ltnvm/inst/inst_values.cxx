#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <iostream>
#include <string>
#include "stdxx/casting.hxx"

namespace ltn::vm::inst {
	void newi(VmCore & core){
		core.stack.push(value::integer(core.fetch_uint()));
	}



	void newf(VmCore & core){
		const std::uint64_t raw = core.fetch_uint();
		core.stack.push(value::floating(stx::bitcast<stx::float64_t>(raw)));
	}



	void newu(VmCore & core){
		core.stack.push(Value{core.fetch_uint(), Value::Type::NVLL});
	}
	


	void newc(VmCore & core) {
		const auto chr = core.fetch_byte();
		core.stack.push(value::character(chr));
	}
	


	void truE(VmCore & core){
		core.stack.push(Value{true, Value::Type::BOOL});
	}



	void falsE(VmCore & core){
		core.stack.push(Value{false, Value::Type::BOOL});
	}



	void null(VmCore & core) {
		core.stack.push(Value{false, Value::Type::NVLL});
	}



	void newi8(VmCore & core) {
		core.stack.push(value::integer(core.fetch_byte()));
	}
}