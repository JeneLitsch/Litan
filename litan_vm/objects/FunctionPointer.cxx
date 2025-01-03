#include "FunctionPointer.hxx"
#include "litan_vm/stdlib/functional.hxx"

namespace ltn::vm {
	void FunctionPointer::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<function>";
	}



	Value FunctionPointer::get_member(VMCore & core, std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::function_arity>       (ReservedMemberCode::ARITY),
			wrap<stdlib::function_is_variadic> (ReservedMemberCode::IS_VARIADIC),
			wrap<stdlib::function_call>        (ReservedMemberCode::CALL),
		};

		return search_native_function_table(native_function_table, id).value_or(value::null);
	}
}