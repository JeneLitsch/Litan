#include "instructions.hxx"
#include "litan_vm/utils/type_check.hxx"
#include "litan_vm/utils/convert.hxx"
#include "litan_vm/utils/special_member.hxx"


namespace ltn::vm::inst {
	#define FETCH const auto x = core.stack.pop();

	void neg(VMCore & core) {
		FETCH
		if(is_bool(x)) {
			return core.stack.push(value::integer(-static_cast<std::int64_t>(x.b)));
		}
		if(is_int(x)) {
			return core.stack.push(value::integer(-x.i));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(-x.f));
		}
		throw except::invalid_argument();
	}



	void n0t(VMCore & core) {
		FETCH
		return core.stack.push(value::boolean(!convert::to_bool(x, core)));
	}



	void inc(VMCore & core) {
		FETCH
		if(is_int(x)) {
			return core.stack.push(value::integer(x.i + 1));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(x.f + 1));
		}
		if(is_struct(x)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_ADD>(core, x, value::integer(1)));
		}
		throw except::invalid_argument();
	}
	
	
	
	void dec(VMCore & core) {
		FETCH
		if(is_int(x)) {
			return core.stack.push(value::integer(x.i - 1));
		}
		if(is_float(x)) {
			return core.stack.push(value::floating(x.f - 1));
		}
		if(is_struct(x)) {
			return core.stack.push(call_special_member<ReservedMemberCode::OPERATOR_SUB>(core, x, value::integer(1)));
		}
		throw except::invalid_argument();
	}

	#undef FETCH
}