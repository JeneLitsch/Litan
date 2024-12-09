#include "Array.hxx"
#include <map>
#include "../NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"
#include "ltnvm/utils/run_function.hxx"
#include "ltnvm/utils/convert.hxx"
#include "ltnvm/native/native.hxx"

namespace ltn::vm {
	namespace {
		Value array_size(Context *, const Value * args) {
			return value::integer(req_array(args + 0)->size());
		}



		Value array_is_empty(Context *, const Value * args) {
			return value::boolean(req_array(args + 0)->empty());
		}



		Value array_push(Context *, const Value * args) {
			req_array(args + 0)->push_back(args[1]);
			return value::null;
		}



		Value array_pop(Context *, const Value * args) {
			Array * array = req_array(args + 0);
			return array->pop_back();
		}



		Value array_front(Context *, const Value * args) {
			return req_array(args + 0)->front();
		}



		Value array_back(Context *, const Value * args) {
			return req_array(args + 0)->back();
		}



		Value array_peek(Context * native_api, const Value * args) {
			return array_back(native_api, args);
		}



		Value array_at(Context *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			return array->at(index);
		}



		Value array_insert(Context *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			Value value = args[2];

			array->insert(index, value);
			return value::null;
		}



		Value array_erase(Context *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			return array->erase(index);
		}



		Value array_filter(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * orig_array = req_array(args + 0);
			Array * dest_array = core.heap.make<Array>();
			for (const Value & elem : *orig_array) {
				const bool result = convert::to_bool(run_function(core, args[1], elem), core);
				if (result) {
					dest_array->push_back(elem);
				}
			}
			return value::array(dest_array);
		}



		Value array_transform(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * orig_array = req_array(args + 0);
			Array * dest_array = core.heap.make<Array>();
			for (const Value & elem : *orig_array) {
				dest_array->push_back(run_function(core, args[1], elem));
			}
			return value::array(dest_array);
		}



		Value array_reduce(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			if(std::empty(*array)) {
				return value::null;
			}

			Value sum = array->unsafe_front();
			VMCore & core = *static_cast<VMCore*>(context->core);
			for (std::size_t i = 1; i < std::size(*array); i++) {
				sum = run_function(core, args[1], sum, array->unsafe_at(i));
			}
			return sum;
		}



		Value array_any(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			VMCore & core = *static_cast<VMCore*>(context->core);
			for (const Value & elem : *array) {
				const Value result = run_function(core, args[1], elem);
				if (convert::to_bool(result, core)) {
					return value::boolean(true);
				}
			}
			return value::boolean(false);
		}



		Value array_all(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			VMCore & core = *static_cast<VMCore*>(context->core);
			for (const Value & elem : *array) {
				const Value result = run_function(core, args[1], elem);
				if (!convert::to_bool(result, core)) {
					return value::boolean(false);
				}
			}
			return value::boolean(true);
		}



		Value array_has(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * array = req_array(args + 0);
			const Value result = args[1];
			for (const Value & elem : *array) {
				if (compare(elem, result, core) == 0) {
					return value::boolean(true);
				}
			}
			return value::boolean(false);
		}



		Value array_none(Context * context, const Value * args) {
			return value::boolean(!array_any(context, args).b);
		}



		Value array_slice(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t begin = req_int(args + 1);
			std::int64_t end = req_int(args + 2);
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * slice = core.heap.alloc(array->slice(begin, end));
			return value::array(slice);
		}



		Value array_prefix(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t size = req_int(args + 1);
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * slice = core.heap.alloc(array->slice(0, size));
			return value::array(slice);
		}



		Value array_suffix(Context * context, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t size = req_int(args + 1);
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * slice = core.heap.alloc(array->slice(static_cast<std::int64_t>(array->size()) - size, array->size()));
			return value::array(slice);
		}



		Value array_reversed(Context * context, const Value * args) {
			VMCore & core = *static_cast<VMCore*>(context->core);
			Array * array = req_array(args + 0);
			Array * reversed = core.heap.alloc(array->reversed());
			return value::array(reversed);
		}



		NativeFunctionTable native_function_table {
			wrap(MemberCode::SIZE,      array_size,        1),
			wrap(MemberCode::IS_EMTPY,  array_is_empty,    1),
			wrap(MemberCode::PUSH,      array_push,        2),
			wrap(MemberCode::POP,       array_pop,         1),
			wrap(MemberCode::FRONT,     array_front,       1),
			wrap(MemberCode::BACK,      array_back,        1),
			wrap(MemberCode::PEEK,      array_peek,        1),
			wrap(MemberCode::AT,        array_at,          2),
			wrap(MemberCode::INSERT,    array_insert,      3),
			wrap(MemberCode::ERASE,     array_erase,       2),
			wrap(MemberCode::FILTER,    array_filter,      2),
			wrap(MemberCode::TRANSFORM, array_transform,   2),
			wrap(MemberCode::REDUCE,    array_reduce,      2),
			wrap(MemberCode::ANY,       array_any,         2),
			wrap(MemberCode::ALL,       array_all,         2),
			wrap(MemberCode::NONE,      array_none,        2),
			wrap(MemberCode::HAS,       array_has,         2),
			wrap(MemberCode::SLICE,     array_slice,       3),
			wrap(MemberCode::PREFIX,    array_prefix,      2),
			wrap(MemberCode::SUFFIX,    array_suffix,      2),
			wrap(MemberCode::REVERSED,  array_reversed,    1),
		};
	}



	Value Array::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}