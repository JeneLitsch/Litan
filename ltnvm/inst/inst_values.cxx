#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include <iostream>
#include <string>
#include "stdxx/casting.hxx"

namespace ltn::vm::inst {
	void newi(VMCore & core){
		core.stack.push(value::integer(core.fetch_uint()));
	}



	void newf(VMCore & core){
		const std::uint64_t raw = core.fetch_uint();
		core.stack.push(value::floating(stx::bitcast<stx::float64_t>(raw)));
	}



	void newc(VMCore & core) {
		const auto chr = core.fetch_byte();
		core.stack.push(value::character(chr));
	}
	


	void truE(VMCore & core){
		core.stack.push(value::boolean(true));
	}



	void falsE(VMCore & core){
		core.stack.push(value::boolean(false));
	}



	void null(VMCore & core) {
		core.stack.push(value::null);
	}



	void newi_small(VMCore & core) {
		core.stack.push(value::integer(static_cast<std::int8_t>(core.fetch_byte())));
	}



	void newi_const_0(VMCore & core) {
		core.stack.push(value::integer(0));
	}



	void newi_const_1(VMCore & core) {
		core.stack.push(value::integer(1));
	}



	void newi_const_2(VMCore & core) {
		core.stack.push(value::integer(2));
	}
}