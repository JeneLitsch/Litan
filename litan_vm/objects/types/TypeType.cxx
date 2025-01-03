#include "TypeType.hxx"
#include "litan_vm/stdlib/type.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {};


	static NativeFunctionTable static_functions {
		wrap<stdlib::type_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::type_is>       (ReservedMemberCode::IS),
	};



	Value TypeType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value TypeType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}