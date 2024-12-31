#pragma once
#include "litan_vm/VMCore.hxx"
#include "litan_vm/Exception.hxx"

namespace ltn::vm::inst {
	
	void exit(VMCore & core);
	void error(VMCore & core);
	void thr0w(VMCore & core);
	void build_in(VMCore & core);

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
	void yield(VMCore & core);
	void co_retvrn(VMCore & core);
	void co_dump(VMCore & core);
	void return_null(VMCore & core);
	void tail(VMCore & core);
	
	void newarr(VMCore & core);
	void newstr(VMCore & core);
	void newfx(VMCore & core);
	void newstruct(VMCore & core);
	void newmap(VMCore & core);
	void newtuple(VMCore & core);
	void newtype(VMCore & core);

	void scrap(VMCore & core);
	void duplicate(VMCore & core);
	void load_x(VMCore & core);
	void store_x(VMCore & core);
	void swap(VMCore & core);
	void unpack(VMCore & core);
	
	void load_0(VMCore & core);
	void load_1(VMCore & core);
	void load_2(VMCore & core);
	void load_3(VMCore & core);
	void store_0(VMCore & core);
	void store_1(VMCore & core);
	void store_2(VMCore & core);
	void store_3(VMCore & core);

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