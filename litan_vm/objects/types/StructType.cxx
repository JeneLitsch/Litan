#include "StructType.hxx"
#include "litan_vm/stdlib/struct.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::struct_new>  (ReservedMemberCode::NEW),
		wrap<stdlib::struct_is>   (ReservedMemberCode::IS),
		wrap<stdlib::struct_cast> (ReservedMemberCode::CAST),
	};



	static NativeFunctionTable nonstatic_functions {};




	Value StructType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}


	Value StructType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}