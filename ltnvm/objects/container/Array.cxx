#include "Array.hxx"
#include <map>
#include "../NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	namespace {
		Array * req_array(const Value & value) {
			if (is_array(value)) {
				return value.as<Array>();
			}
			else {
				throw except::invalid_argument();
			}	
		}



		Value array_size(const Value * args) {
			return value::integer(req_array(args[0])->size());
		}



		Value array_is_empty(const Value * args) {
			return value::boolean(req_array(args[0])->empty());
		}



		Value array_push(const Value * args) {
			req_array(args[0])->push_back(args[1]);
			return value::null;
		}



		Value array_pop(const Value * args) {
			Array * array = req_array(args[0]);
			if(std::empty(*array)) throw except::out_of_range();
			Value val = array->back();
			array->pop_back();
			return val;
		}



		std::map<std::uint64_t, NativeFunctionPointer> native_function_table {
			{ static_cast<std::uint64_t>(MemberCode::SIZE), NativeFunctionPointer{array_size, 1, false} },
			{ static_cast<std::uint64_t>(MemberCode::IS_EMTPY), NativeFunctionPointer{array_is_empty, 1, false} },
			{ static_cast<std::uint64_t>(MemberCode::PUSH), NativeFunctionPointer{array_push, 2, false} },
			{ static_cast<std::uint64_t>(MemberCode::POP), NativeFunctionPointer{array_pop, 1, false} },
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