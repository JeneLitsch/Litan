#include "MapType.hxx"
#include "litan_vm/stdlib/map.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::map_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::map_is>       (ReservedMemberCode::IS),
		wrap<stdlib::map_cast>     (ReservedMemberCode::CAST),
	};

	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::map_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::map_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::map_at>       (ReservedMemberCode::AT),
		wrap<stdlib::map_has>      (ReservedMemberCode::HAS),
		wrap<stdlib::map_insert>   (ReservedMemberCode::INSERT),
		wrap<stdlib::map_erase>    (ReservedMemberCode::ERASE),
		wrap<stdlib::map_keys>     (ReservedMemberCode::KEYS),
		wrap<stdlib::map_values>   (ReservedMemberCode::VALUES),
		wrap<stdlib::map_merged>   (ReservedMemberCode::MERGED),
	};




	Value MapType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}


	Value MapType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}