#include "type.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/objects/container/Array.hxx"
#include "litan_vm/inst/instructions.hxx"

namespace ltn::vm::stdlib {
	Value id::func(ltn_Context * context, const Value * args) {
		return value::integer(static_cast<std::int64_t>(args[0].type));
	}



	Value clone::func(ltn_Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const auto ref = args[0];
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



	Value is::func(ltn_Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const auto value = args[1];
		const auto type_ref = args[0];
		if(!is_type(type_ref)) throw except::invalid_operands();
		auto * type = value::as_type_object(type_ref);
		return value::boolean(type_is(*type, value, core));
	}



	Value cast::func(ltn_Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const auto value = args[1];
		const auto ref = args[0];
		if(!is_type(ref)) throw except::invalid_operands();
		auto * type = value::as_type_object(ref);
		return type_cast(*type, value, core);
	}



	Value type_array::func(ltn_Context * context, const Value * args) {
		static ArrayType type;
		return value::static_object(&type);
	}
}