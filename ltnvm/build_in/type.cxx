#include "type.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm::build_in::type {
	Value id(VmCore & core) {
		const auto value = core.stack.pop();
		return value::integer(static_cast<std::int64_t>(value.type));
	}



	Value clone(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref)) return Value{core.heap.clone<Array>(ref.ptr), ref.type};
		if(is_string(ref)) return Value{core.heap.clone<String>(ref.ptr), ref.type};
		if(is_stack(ref)) return Value{core.heap.clone<Deque>(ref.ptr), ref.type};
		if(is_queue(ref)) return Value{core.heap.clone<Deque>(ref.ptr), ref.type};
		if(is_map(ref)) return Value{core.heap.clone<Map>(ref.ptr), ref.type};
		if(is_ostream(ref)) return Value{core.heap.clone<OStream>(ref.ptr), ref.type};
		if(is_istream(ref)) return Value{core.heap.clone<IStream>(ref.ptr), ref.type};
		if(is_rng(ref)) return Value{core.heap.clone<RandomEngine>(ref.ptr), ref.type};
		if(is_struct(ref)) return Value{core.heap.clone<Struct>(ref.ptr), ref.type};
		throw except::invalid_argument("Cannot clone");
	}
}