#include "Array.hxx"
#include <map>
#include "../NativeFunctionPointer.hxx"
#include "ltn/MemberCode.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/VMCore.hxx"
#include "ltnvm/utils/type_check.hxx"

namespace ltn::vm {
	namespace {
		Value array_size(const Value * args) {
			if (is_array(args[0])) {
				return value::integer(args->as<Array>()->size());
			}
			else {
				throw except::invalid_argument();
			}
		}

		std::map<std::uint64_t, NativeFunctionPointer> native_function_table {
			{ static_cast<std::uint64_t>(MemberCode::SIZE), NativeFunctionPointer{array_size, 1, false} },
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