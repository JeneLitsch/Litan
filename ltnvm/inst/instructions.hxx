#pragma once
#include "ltnvm/VMCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::inst {
	
	void exit(VMCore & core);
	void error(VMCore & core);
	void tRy(VMCore & core);
	void thr0w(VMCore & core);
	void build_in(VMCore & core);
	void yield(VMCore & core);

	void add(VMCore & core);
	void sub(VMCore & core);
	void mlt(VMCore & core);
	void div(VMCore & core);
	void mod(VMCore & core);
	void pow(VMCore & core);
	 
	void eql(VMCore & core);
	void ueql(VMCore & core);
	void lt(VMCore & core);
	void gt(VMCore & core);
	void bgreql(VMCore & core);
	void smleql(VMCore & core);
	
	void shift_l(VMCore & core);
	void shift_r(VMCore & core);
	
	void neg(VMCore & core);
	void n0t(VMCore & core);
	void inc(VMCore & core);
	void dec(VMCore & core);
	void comp(VMCore & core);
	void deref(VMCore & core);

	void newi(VMCore & core);
	void newf(VMCore & core);
	void newc(VMCore & core);
	void truE(VMCore & core);
	void falsE(VMCore & core);
	void null(VMCore & core);
	void newi_small(VMCore & core);
	
	void jump(VMCore & core);
	void call(VMCore & core);
	void reTurn(VMCore & core);
	void iF(VMCore & core);
	void invoke(VMCore & core);
	void invoke_variadic(VMCore & core);
	void capture(VMCore & core);
	void for_next(VMCore & core);
	
	void newarr(VMCore & core);
	void newstr(VMCore & core);
	void newfx(VMCore & core);
	void newclock(VMCore & core);
	void newstruct(VMCore & core);
	void newstack(VMCore & core);
	void newqueue(VMCore & core);
	void newmap(VMCore & core);
	void newtuple(VMCore & core);
	void newtype(VMCore & core);

	void scrap(VMCore & core);
	void duplicate(VMCore & core);
	void alloc_local(VMCore & core);
	void read_x(VMCore & core);
	void write_x(VMCore & core);
	void swap(VMCore & core);
	void unpack(VMCore & core);
	
	void read_0(VMCore & core);
	void read_1(VMCore & core);
	void read_2(VMCore & core);
	void read_3(VMCore & core);
	void write_0(VMCore & core);
	void write_1(VMCore & core);
	void write_2(VMCore & core);
	void write_3(VMCore & core);

	void newi_const_0(VMCore & core);
	void newi_const_1(VMCore & core);
	void newi_const_2(VMCore & core);

	void bit_or(VMCore & core);
	void bit_and(VMCore & core);
	void bit_xor(VMCore & core);
	void bit_not(VMCore & core);
	
	void at(VMCore & core);
	void at_write(VMCore & core);
	void iter(VMCore & core);

	void cast_bool(VMCore & core);

	void member_read(VMCore & core);
	void member_write(VMCore & core);
	void static_read(VMCore & core);
	void static_write(VMCore & core);
}