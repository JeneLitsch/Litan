#include "instructions.hxx"
#include "ltnvm/type_check.hxx"
#include "ltnvm/convert.hxx"


namespace ltn::vm::inst {
	#define FETCH const auto x = core.stack.pop();

	void neg(VmCore & core) {
		FETCH
		if(is_bool(x)) {
			return core.stack.push({- static_cast<std::int64_t>(x.b)});
		}
		if(is_char(x)) {
			return core.stack.push({- static_cast<std::int64_t>(x.c)});
		}
		if(is_int(x)) {
			return core.stack.push({- x.i});
		}
		if(is_float(x)) {
			return core.stack.push({- x.f});
		}
		throw except::invalid_argument();
	}



	void n0t(VmCore & core) {
		FETCH
		return core.stack.push(!convert::to_bool(x, core));
	}



	void inc(VmCore & core) {
		FETCH
		if(is_char(x)) {
			return core.stack.push(static_cast<char>(x.c + 1));
		}
		if(is_int(x)) {
			return core.stack.push({x.i + 1});
		}
		if(is_float(x)) {
			return core.stack.push({x.f + 1});
		}
		throw except::invalid_argument();
	}
	
	
	
	void dec(VmCore & core) {
		FETCH
		if(is_char(x)) {
			return core.stack.push(static_cast<char>(x.c - 1));
		}
		if(is_int(x)) {
			return core.stack.push({x.i - 1});
		}
		if(is_float(x)) {
			return core.stack.push({x.f - 1});
		}
		throw except::invalid_argument();
	}

	#undef FETCH
}