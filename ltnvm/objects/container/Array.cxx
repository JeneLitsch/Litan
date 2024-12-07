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
		Value array_size(NativeCore *, const Value * args) {
			return value::integer(req_array(args + 0)->size());
		}



		Value array_is_empty(NativeCore *, const Value * args) {
			return value::boolean(req_array(args + 0)->empty());
		}



		Value array_push(NativeCore *, const Value * args) {
			req_array(args + 0)->push_back(args[1]);
			return value::null;
		}



		Value array_pop(NativeCore *, const Value * args) {
			Array * array = req_array(args + 0);
			if(std::empty(*array)) {
				throw except::out_of_range();
			}
			Value val = array->back();
			array->pop_back();
			return val;
		}



		Value array_front(NativeCore *, const Value * args) {
			return req_array(args + 0)->front();
		}



		Value array_back(NativeCore *, const Value * args) {
			return req_array(args + 0)->back();
		}



		Value array_peek(NativeCore * native_api, const Value * args) {
			return array_back(native_api, args);
		}



		Value array_at(NativeCore *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			if(std::size(*array) <= index) {
				throw except::out_of_range();
			}
			return (*array)[index];
		}



		Value array_insert(NativeCore *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			Value value = args[2];
			if(std::size(*array) + 1 <= index) {
				throw except::out_of_range();
			}
			array->insert(std::begin(*array) + index, value);
			return value::null;
		}



		Value array_erase(NativeCore *, const Value * args) {
			Array * array = req_array(args + 0);
			std::int64_t index = req_int(args + 1);
			if(std::size(*array) <= index) {
				throw except::out_of_range();
			}
			Value value = (*array)[index];
			array->erase(std::begin(*array) + index);
			return value;
		}



		Value array_filter(NativeCore * native_core, const Value * args) {
			Array * orig_array = req_array(args + 0);
			std::vector<Value> dest_array;
			VMCore & core = *static_cast<VMCore*>(native_core->core);
			for (const Value & elem : *orig_array) {
				const bool result = convert::to_bool(run_function(core, args[1], elem), core);
				if (result) {
					dest_array.push_back(elem);
				}
			}
			return native_core->alloc_array(native_core, std::data(dest_array), std::size(dest_array));
		}



		Value array_transform(NativeCore * native_core, const Value * args) {
			Array * orig_array = req_array(args + 0);
			std::vector<Value> dest_array;
			VMCore & core = *static_cast<VMCore*>(native_core->core);
			for (const Value & elem : *orig_array) {
				dest_array.push_back(run_function(core, args[1], elem));
			}
			return native_core->alloc_array(native_core, std::data(dest_array), std::size(dest_array));
		}



		Value array_reduce(NativeCore * native_core, const Value * args) {
			Array * array = req_array(args + 0);
			if(std::empty(*array)) {
				return value::null;
			}

			Value sum = array->front();
			VMCore & core = *static_cast<VMCore*>(native_core->core);
			for (std::size_t i = 1; i < std::size(*array); i++) {
				sum = run_function(core, args[1], sum, (*array)[i]);
			}
			return sum;
		}



		Value array_any(NativeCore * native_core, const Value * args) {
			Array * array = req_array(args + 0);
			VMCore & core = *static_cast<VMCore*>(native_core->core);
			for (const Value & elem : *array) {
				const Value result = run_function(core, args[1], elem);
				if (convert::to_bool(result, core)) {
					return value::boolean(true);
				}
			}
			return value::boolean(false);
		}



		Value array_all(NativeCore * native_core, const Value * args) {
			Array * array = req_array(args + 0);
			VMCore & core = *static_cast<VMCore*>(native_core->core);
			for (const Value & elem : *array) {
				const Value result = run_function(core, args[1], elem);
				if (!convert::to_bool(result, core)) {
					return value::boolean(false);
				}
			}
			return value::boolean(true);
		}



		Value array_none(NativeCore * native_core, const Value * args) {
			return value::boolean(!array_any(native_core, args).b);
		}




		NativeFunctionTable native_function_table {
			wrap(MemberCode::SIZE,      array_size,      1),
			wrap(MemberCode::IS_EMTPY,  array_is_empty,  1),
			wrap(MemberCode::PUSH,      array_push,      2),
			wrap(MemberCode::POP,       array_pop,       1),
			wrap(MemberCode::FRONT,     array_front,     1),
			wrap(MemberCode::BACK,      array_back,      1),
			wrap(MemberCode::PEEK,      array_peek,      1),
			wrap(MemberCode::AT,        array_at,        2),
			wrap(MemberCode::INSERT,    array_insert,    3),
			wrap(MemberCode::ERASE,     array_erase,     2),
			wrap(MemberCode::FILTER,    array_filter,    2),
			wrap(MemberCode::TRANSFORM, array_transform, 2),
			wrap(MemberCode::REDUCE,    array_reduce,    2),
			wrap(MemberCode::ANY,       array_any,      2),
			wrap(MemberCode::ALL,       array_all,     2),
			wrap(MemberCode::NONE,      array_none,      2),
		};
	}



	Value Array::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}