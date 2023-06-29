#include "type.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/inst/instructions.hxx"

namespace ltn::vm::build_in::type {
	Value id(VmCore & core) {
		const auto value = core.stack.pop();
		return value::integer(static_cast<std::int64_t>(value.type));
	}



	Value clone(VmCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref))    return core.heap.clone<Array>(ref);
		if(is_string(ref))   return core.heap.clone<String>(ref);
		if(is_stack(ref))    return core.heap.clone<Deque>(ref);
		if(is_queue(ref))    return core.heap.clone<Deque>(ref);
		if(is_map(ref))      return core.heap.clone<Map>(ref);
		if(is_ostream(ref))  return core.heap.clone<OStream>(ref);
		if(is_istream(ref))  return core.heap.clone<IStream>(ref);
		if(is_rng(ref))      return core.heap.clone<RandomEngine>(ref);
		if(is_struct(ref))   return core.heap.clone<Struct>(ref);
		if(is_iterator(ref)) return core.heap.clone<Iterator>(ref);
		throw except::invalid_argument("Cannot clone");
	}



	Value is(VmCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(!is_type(ref)) throw except::invalid_operands();
		auto * type = ref.obj_type;
		return type_is(*type, value, core);
	}



	Value cast(VmCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(!is_type(ref)) throw except::invalid_operands();
		auto * type = ref.obj_type;
		return type_cast(*type, value, core);
	}



	Value queue(VmCore & core) {
		inst::newqueue(core);
		return core.stack.pop();
	}



	Value stack(VmCore & core) {
		inst::newstack(core);
		return core.stack.pop();
	}



	Value map(VmCore & core) {
		inst::newmap(core);
		return core.stack.pop();
	}
}