#include "FunctionType.hxx"
#include "litan_vm/stdlib/functional.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
			wrap<stdlib::function_arity>       (ReservedMemberCode::ARITY),
			wrap<stdlib::function_is_variadic> (ReservedMemberCode::IS_VARIADIC),
			wrap<stdlib::function_call>        (ReservedMemberCode::CALL),
	};


	static NativeFunctionTable static_functions {
		wrap<stdlib::function_cast>            (ReservedMemberCode::CAST),
		wrap<stdlib::function_is>              (ReservedMemberCode::IS),
	};



	Value FunctionType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value FunctionType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}