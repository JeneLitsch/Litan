#include "Array.hxx"
#include <map>
#include "../NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"
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




		NativeFunctionTable native_function_table {
			wrap(MemberCode::SIZE,     array_size,     1),
			wrap(MemberCode::IS_EMTPY, array_is_empty, 1),
			wrap(MemberCode::PUSH,     array_push,     2),
			wrap(MemberCode::POP,      array_pop,      1),
			wrap(MemberCode::FRONT,    array_front,    1),
			wrap(MemberCode::BACK,     array_back,     1),
			wrap(MemberCode::PEEK,     array_peek,     1),
			wrap(MemberCode::AT,       array_at,       2),
			wrap(MemberCode::INSERT,   array_insert,   3),
			wrap(MemberCode::ERASE,    array_erase,    2),
		};
	}



	Value Array::get_member(std::uint64_t id) const {
		return search_native_function_table(native_function_table, id);
	}
}