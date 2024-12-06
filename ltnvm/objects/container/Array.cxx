#include "Array.hxx"
#include <map>
#include "../NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	namespace {
		Array * cast_array(const Value & value) {
			if (is_array(value)) {
				return value.as<Array>();
			}
			else {
				throw except::invalid_argument();
			}
		}



		std::int64_t cast_int(const Value & value) {
			if (is_int(value)) {
				return value.i;
			}
			else {
				throw except::invalid_argument();
			}
		}



		Value array_size(const Value * args) {
			return value::integer(cast_array(args[0])->size());
		}



		Value array_is_empty(const Value * args) {
			return value::boolean(cast_array(args[0])->empty());
		}



		Value array_push(const Value * args) {
			cast_array(args[0])->push_back(args[1]);
			return value::null;
		}



		Value array_pop(const Value * args) {
			Array * array = cast_array(args[0]);
			if(std::empty(*array)) throw except::out_of_range();
			Value val = array->back();
			array->pop_back();
			return val;
		}



		Value array_front(const Value * args) {
			return cast_array(args[0])->front();
		}



		Value array_back(const Value * args) {
			return cast_array(args[0])->back();
		}



		Value array_peek(const Value * args) {
			return array_back(args);
		}



		Value array_at(const Value * args) {
			Array * array = cast_array(args[0]);
			std::int64_t index = cast_int(args[1]);
			if(std::size(*array) <= index) throw except::out_of_range();
			return (*array)[index];
		}



		Value array_insert(const Value * args) {
			Array * array = cast_array(args[0]);
			std::int64_t index = cast_int(args[1]);
			Value value = args[2];
			array->insert(std::begin(*array) + index, value);
			return value::null;
		}



		Value array_erase(const Value * args) {
			Array * array = cast_array(args[0]);
			std::int64_t index = cast_int(args[1]);
			if(std::size(*array) <= index) throw except::out_of_range();
			Value value = (*array)[index];
			array->erase(std::begin(*array) + index);
			return value;
		}



		std::pair<std::uint64_t, NativeFunctionPointer> wrap(MemberCode code, NativeFunctionHandle handle, std::uint64_t arity) {
			return std::pair<std::uint64_t, NativeFunctionPointer>{ static_cast<std::uint64_t>(code), NativeFunctionPointer{handle, arity, false} };
		}



		std::map<std::uint64_t, NativeFunctionPointer> native_function_table {
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
		if (native_function_table.contains(id)) {
			return value::native_function(&native_function_table.at(id));
		}
		else {
			return value::null;
		}
	}
}