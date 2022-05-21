#pragma once
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::inst {
	
	void exit(VmCore & core);
	void error(VmCore & core);
	void state(VmCore & core);
	void tRy(VmCore & core);
	void thr0w(VmCore & core);

	void add(VmCore & core);
	void sub(VmCore & core);
	void mlt(VmCore & core);
	void div(VmCore & core);
	void mod(VmCore & core);
	
	 
	void eql(VmCore & core);
	void ueql(VmCore & core);
	void sml(VmCore & core);
	void bgr(VmCore & core);
	void bgreql(VmCore & core);
	void smleql(VmCore & core);
	
	void shift_l(VmCore & core);
	void shift_r(VmCore & core);
	
	
	void neg(VmCore & core);
	void n0t(VmCore & core);
	void inc(VmCore & core);
	void dec(VmCore & core);
	void comp(VmCore & core);
	void approx(VmCore & core);

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
	void between(VmCore & core);
	void external(VmCore & core);
	void capture(VmCore & core);
	void parameters(VmCore & core);
	
	void newarr(VmCore & core);
	void newstr(VmCore & core);
	void newout(VmCore & core);
	void newin(VmCore & core);
	void newfx(VmCore & core);
	void newclock(VmCore & core);
	void newstruct(VmCore & core);
	void newrange(VmCore & core);
	void newstack(VmCore & core);
	void newqueue(VmCore & core);
	void newmap(VmCore & core);
	void newrng(VmCore & core);

	void read(VmCore & core);
	void write(VmCore & core);
	void scrap(VmCore & core);
	void duplicate(VmCore & core);
	void makevar(VmCore & core);
	void read_x(VmCore & core);
	void write_x(VmCore & core);
	void swap(VmCore & core);
	
	void read_0(VmCore & core);
	void read_1(VmCore & core);
	void read_2(VmCore & core);
	void read_3(VmCore & core);
	void write_0(VmCore & core);
	void write_1(VmCore & core);
	void write_2(VmCore & core);
	void write_3(VmCore & core);

	void out(VmCore & core);
	void close_stream(VmCore & core);
	void stylize(VmCore & core);
	void in_str(VmCore & core);
	void in_line(VmCore & core);
	void in_bool(VmCore & core);
	void in_char(VmCore & core);
	void in_int(VmCore & core);
	void in_float(VmCore & core);
	void in_all(VmCore & core);
	void is_eof(VmCore & core);
	void is_good(VmCore & core);

	void min(VmCore & core);
	void max(VmCore & core);
	void round(VmCore & core);
	void floor(VmCore & core);
	void ceil(VmCore & core);
	void abs(VmCore & core);
	void hypot(VmCore & core);
	void sqrt(VmCore & core);
	void log(VmCore & core);
	void ln(VmCore & core);
	void pow(VmCore & core);
	
	void sin(VmCore & core);
	void cos(VmCore & core);
	void tan(VmCore & core);

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
	void begin(VmCore & core);
	void end(VmCore & core);
	void push(VmCore & core);
	void pop(VmCore & core);
	void peek(VmCore & core);
	void contains(VmCore & core);
	
	void cast_bool(VmCore & core);
	void cast_char(VmCore & core);
	void cast_int(VmCore & core);
	void cast_float(VmCore & core);
	void cast_string(VmCore & core);
	void cast_array(VmCore & core);

	void type_id(VmCore & core);
	void clone(VmCore & core);

	void member_read(VmCore & core);
	void member_write(VmCore & core);

	void algorithm(VmCore & core);
	void random(VmCore & core);
}