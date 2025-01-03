#include "type.hxx"
#include "litan_vm/Exception.hxx"
#include "litan_vm/objects/container/Array.hxx"
#include "litan_vm/inst/instructions.hxx"
#include "litan_vm/utils/function.hxx"

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
		if (is_type(type_ref)) {
			StaticObject * so = value::as<StaticObject>(type_ref);
			Value cast_function = so->get_member(core, static_cast<std::uint64_t>(ReservedMemberCode::IS));
			return invoke_function_immediatly(core, cast_function, args + 1, 1);
		}
		throw except::invalid_operands();
	}



	Value cast::func(ltn_Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		const auto value = args[1];
		const auto type_ref = args[0];
		if (is_type(type_ref)) {
			StaticObject * so = value::as<StaticObject>(type_ref);
			Value cast_function = so->get_member(core, static_cast<std::uint64_t>(ReservedMemberCode::CAST));
			try {
				return invoke_function_immediatly(core, cast_function, args + 1, 1);
			}
			catch(...) {
				return value::null;
			}
		}
		throw except::invalid_operands();
	}



	Value stop_new::func(ltn_Context * context, const Value * args) {
		return value::iterator_stop;
	}



	Value stop_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_iterator_stop(args[0]));
	}



	Value stop_cast::func(ltn_Context * context, const Value * args) {
		return is_iterator_stop(args[0]) ? args[0] : value::null;
	}



	Value type_is::func(ltn_Context * context, const Value * args) {
		return value::boolean(is_type(args[0]));
	}



	Value type_cast::func(ltn_Context * context, const Value * args) {
		return is_type(args[0]) ? args[0] : value::null;
	}
}