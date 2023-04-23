#pragma once
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::inst {
	
	void exit(VmCore & core);
	void error(VmCore & core);
	void tRy(VmCore & core);
	void thr0w(VmCore & core);
	void build_in(VmCore & core);

	void add(VmCore & core);
	void sub(VmCore & core);
	void mlt(VmCore & core);
	void div(VmCore & core);
	void mod(VmCore & core);
	
	 
	void eql(VmCore & core);
	void ueql(VmCore & core);
	void lt(VmCore & core);
	void gt(VmCore & core);
	void bgreql(VmCore & core);
	void smleql(VmCore & core);
	
	void shift_l(VmCore & core);
	void shift_r(VmCore & core);
	
	
	void neg(VmCore & core);
	void n0t(VmCore & core);
	void inc(VmCore & core);
	void dec(VmCore & core);
	void comp(VmCore & core);
	void deref(VmCore & core);

	void newi(VmCore & core);
	void newf(VmCore & core);
	void newu(VmCore & core);
	void newc(VmCore & core);
	void truE(VmCore & core);
	void falsE(VmCore & core);
	void null(VmCore & core);
	
	void jump(VmCore & core);
	void call(VmCore & core);
	void reTurn(VmCore & core);
	void iF(VmCore & core);
	void invoke(VmCore & core);
	void invoke_variadic(VmCore & core);
	void between(VmCore & core);
	void capture(VmCore & core);
	void for_next(VmCore & core);
	
	void newarr(VmCore & core);
	void newstr(VmCore & core);
	void newfx(VmCore & core);
	void newclock(VmCore & core);
	void newstruct(VmCore & core);
	void newstack(VmCore & core);
	void newqueue(VmCore & core);
	void newmap(VmCore & core);
	void newtuple(VmCore & core);

	void scrap(VmCore & core);
	void duplicate(VmCore & core);
	void makevar(VmCore & core);
	void read_x(VmCore & core);
	void write_x(VmCore & core);
	void swap(VmCore & core);
	void unpack(VmCore & core);
	
	void read_0(VmCore & core);
	void read_1(VmCore & core);
	void read_2(VmCore & core);
	void read_3(VmCore & core);
	void write_0(VmCore & core);
	void write_1(VmCore & core);
	void write_2(VmCore & core);
	void write_3(VmCore & core);

	void pow(VmCore & core);

	void bit_or(VmCore & core);
	void bit_and(VmCore & core);
	void bit_xor(VmCore & core);
	void bit_not(VmCore & core);
	
	void size(VmCore & core);
	void at(VmCore & core);
	void at_write(VmCore & core);
	void front(VmCore & core);
	void back(VmCore & core);
	void insert(VmCore & core);
	void remove(VmCore & core);
	void push(VmCore & core);
	void pop(VmCore & core);
	void peek(VmCore & core);
	void contains(VmCore & core);
	void empty(VmCore & core);
	void iter(VmCore & core);
	void next(VmCore & core);
	void done(VmCore & core);

	void cast(VmCore & core);
	void safe_cast(VmCore & core);

	void cast_bool(VmCore & core);
	void cast_char(VmCore & core);
	void cast_int(VmCore & core);
	void cast_float(VmCore & core);
	void cast_string(VmCore & core);

	void copy(VmCore & core);
	void safe_copy(VmCore & core);
	void conversion(VmCore & core);

	void member_read(VmCore & core);
	void member_write(VmCore & core);
	void static_read(VmCore & core);
	void static_write(VmCore & core);
}