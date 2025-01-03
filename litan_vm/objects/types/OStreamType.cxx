#include "OStreamType.hxx"
#include "litan_vm/stdlib/io.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {};


	static NativeFunctionTable static_functions {
		// wrap<stdlib::istream_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::ostream_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::ostream_is>       (ReservedMemberCode::IS),
	};



	Value OStreamType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value OStreamType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}