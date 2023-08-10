#include "instructions.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/utils/special_member.hxx"


namespace ltn::vm::inst {
	#define FETCH const auto x = core.stack.pop();

	void neg(VmCore & core) {
		FETCH
		if(is_bool(x)) {
			return core.stack.push(value::integer(-static_cast<std::int64_t>(x.b)));
		}
		if(is_char(x)) {
			return core.stack.push(value::integer(-static_cast<std::int64_t>(x.c)));
		}
		if(is_int(x)) {
			return core.stack.push(value::integer(-x.i));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(-x.f));
		}
		throw except::invalid_argument();
	}



	void n0t(VmCore & core) {
		FETCH
		return core.stack.push(value::boolean(!convert::to_bool(x, core)));
	}



	void inc(VmCore & core) {
		FETCH
		if(is_char(x)) {
			return core.stack.push(value::integer(static_cast<char>(x.c + 1)));
		}
		if(is_int(x)) {
			return core.stack.push(value::integer(x.i + 1));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(x.f + 1));
		}
		if(is_struct(x)) {
			return core.stack.push(call_special_member<MemberCode::ADD>(core, x, value::integer(1)));
		}
		throw except::invalid_argument();
	}
	
	
	
	void dec(VmCore & core) {
		FETCH
		if(is_char(x)) {
			return core.stack.push(value::integer(static_cast<char>(x.c - 1)));
		}
		if(is_int(x)) {
			return core.stack.push(value::integer(x.i - 1));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(x.f - 1));
		}
		if(is_struct(x)) {
			return core.stack.push(call_special_member<MemberCode::SUB>(core, x, value::integer(1)));
		}
		throw except::invalid_argument();
	}

	#undef FETCH
}