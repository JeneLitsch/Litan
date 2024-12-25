#include "type.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/inst/instructions.hxx"

namespace ltn::vm::build_in::type {
	Value id(VMCore & core) {
		const auto value = core.stack.pop();
		return value::integer(static_cast<std::int64_t>(value.type));
	}



	Value clone(VMCore & core) {
		const auto ref = core.stack.pop();
		if(is_array(ref))    return core.heap.clone<Array>(ref);
		if(is_tuple(ref))    return core.heap.clone<Tuple>(ref);
		if(is_string(ref))   return core.heap.clone<String>(ref);
		if(is_stack(ref))    return core.heap.clone<Stack>(ref);
		if(is_queue(ref))    return core.heap.clone<Queue>(ref);
		if(is_map(ref))      return core.heap.clone<Map>(ref);
		if(is_ostream(ref))  return core.heap.clone<OStream>(ref);
		if(is_istream(ref))  return core.heap.clone<IStream>(ref);
		if(is_rng(ref))      return core.heap.clone<RandomEngine>(ref);
		if(is_struct(ref))   return core.heap.clone<Struct>(ref);
		if(is_iterator(ref)) {
			return value::iterator(core.heap.track(value::as<Iterator>(ref)->clone()));
		}
		throw except::invalid_argument("Cannot clone");
	}



	Value is(VMCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(!is_type(ref)) throw except::invalid_operands();
		auto * type = value::as_type_object(ref);
		return value::boolean(type_is(*type, value, core));
	}



	Value cast(VMCore & core) {
		const auto value = core.stack.pop();
		const auto ref = core.stack.pop();
		if(!is_type(ref)) throw except::invalid_operands();
		auto * type = value::as_type_object(ref);
		return type_cast(*type, value, core);
	}



	Value queue(VMCore & core) {
		inst::newqueue(core);
		return core.stack.pop();
	}



	Value stack(VMCore & core) {
		inst::newstack(core);
		return core.stack.pop();
	}



	Value map(VMCore & core) {
		inst::newmap(core);
		return core.stack.pop();
	}
}