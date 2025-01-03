#include "TupleType.hxx"
#include "litan_vm/stdlib/tuple.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::tuple_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::tuple_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::tuple_at>       (ReservedMemberCode::AT),
		wrap<stdlib::tuple_front>    (ReservedMemberCode::FRONT),
		wrap<stdlib::tuple_back>     (ReservedMemberCode::BACK),
		wrap<stdlib::tuple_values>   (ReservedMemberCode::VALUES),
	};



	static NativeFunctionTable static_functions {
		wrap<stdlib::tuple_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::tuple_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::tuple_is>       (ReservedMemberCode::IS),
	};



	Value TupleType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value TupleType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}