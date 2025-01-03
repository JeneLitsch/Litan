#include "NullType.hxx"
#include "litan_vm/stdlib/null.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::null_new> (ReservedMemberCode::NEW),
		wrap<stdlib::null_is>  (ReservedMemberCode::IS),
		wrap<stdlib::null_cast>  (ReservedMemberCode::CAST),
	};



	Value NullType::get_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(static_functions, id).value_or(value::null);
	}
}