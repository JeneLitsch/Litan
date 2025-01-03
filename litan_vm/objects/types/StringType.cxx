#include "StringType.hxx"
#include "litan_vm/stdlib/string.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::string_new>  (ReservedMemberCode::NEW),
		wrap<stdlib::string_is>   (ReservedMemberCode::IS),
		wrap<stdlib::string_cast> (ReservedMemberCode::CAST),
	};

	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::string_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::string_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::string_split>    (ReservedMemberCode::SPLIT),
	};




	Value StringType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}


	Value StringType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}