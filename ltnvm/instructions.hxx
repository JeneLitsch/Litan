#pragma once
#include "ltnvm/VmCore.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::inst {
	void
		state(VmCore & core),
		tRy(VmCore & core),
		thr0w(VmCore & core);

	void
		add(VmCore & core),
		sub(VmCore & core),
		mlt(VmCore & core),
		div(VmCore & core),
		mod(VmCore & core);
	
	void 
		eql(VmCore & core),
		ueql(VmCore & core),
		sml(VmCore & core),
		bgr(VmCore & core),
		bgreql(VmCore & core),
		smleql(VmCore & core);
	
	void
		shift_l(VmCore & core),
		shift_r(VmCore & core);
	
	void
		neg(VmCore & core),
		n0t(VmCore & core),
		inc(VmCore & core),
		dec(VmCore & core),
		comp(VmCore & core),
		approx(VmCore & core);

	void
		newi(VmCore & core),
		newf(VmCore & core),
		newu(VmCore & core),
		newc(VmCore & core),
		truE(VmCore & core),
		falsE(VmCore & core),
		null(VmCore & core);
	
	void
		jump(VmCore & core),
		call(VmCore & core),
		reTurn(VmCore & core),
		iF(VmCore & core),
		invoke(VmCore & core),
		between(VmCore & core),
		external(VmCore & core),
		capture(VmCore & core),
		parameters(VmCore & core);
	
	void
		newarr(VmCore & core),
		newstr(VmCore & core),
		newout(VmCore & core),
		newin(VmCore & core),
		newfx(VmCore & core),
		newclock(VmCore & core),
		newstruct(VmCore & core),
		newrange(VmCore & core),
		newstack(VmCore & core),
		newqueue(VmCore & core),
		newmap(VmCore & core),
		newrng(VmCore & core);

	void
		read(VmCore & core),
		write(VmCore & core),
		scrap(VmCore & core),
		duplicate(VmCore & core),
		makevar(VmCore & core),
		read_x(VmCore & core),
		write_x(VmCore & core),
		swap(VmCore & core);
	
	void
		read_0(VmCore & core),
		read_1(VmCore & core),
		read_2(VmCore & core),
		read_3(VmCore & core),
		write_0(VmCore & core),
		write_1(VmCore & core),
		write_2(VmCore & core),
		write_3(VmCore & core);

	void
		out(VmCore & core),
		close_stream(VmCore & core),
		stylize(VmCore & core),
		in_str(VmCore & core),
		in_line(VmCore & core),
		in_bool(VmCore & core),
		in_char(VmCore & core),
		in_int(VmCore & core),
		in_float(VmCore & core),
		in_all(VmCore & core),
		is_eof(VmCore & core),
		is_good(VmCore & core);

	void
		min(VmCore & core),
		max(VmCore & core),
		round(VmCore & core),
		floor(VmCore & core),
		ceil(VmCore & core),
		abs(VmCore & core),
		hypot(VmCore & core),
		sqrt(VmCore & core),
		log(VmCore & core),
		ln(VmCore & core),
		pow(VmCore & core);
	
	void
		sin(VmCore & core),
		cos(VmCore & core),
		tan(VmCore & core);

	void
		bit_or(VmCore & core),
		bit_and(VmCore & core),
		bit_xor(VmCore & core),
		bit_not(VmCore & core);
	
	void
		size(VmCore & core),
		at(VmCore & core),
		at_write(VmCore & core),
		front(VmCore & core),
		back(VmCore & core),
		insert(VmCore & core),
		remove(VmCore & core),
		begin(VmCore & core),
		end(VmCore & core),
		push(VmCore & core),
		pop(VmCore & core),
		peek(VmCore & core),
		contains(VmCore & core);
	
	void
		cast_bool(VmCore & core),
		cast_char(VmCore & core),
		cast_int(VmCore & core),
		cast_float(VmCore & core),
		cast_string(VmCore & core),
		cast_array(VmCore & core);

	void
		type_id(VmCore & core),
		clone(VmCore & core);

	void
		member_read(VmCore & core),
		member_write(VmCore & core);

	void 
		algorithm(VmCore & core),
		random(VmCore & core);
}