#include "BoolType.hxx"
#include "litan_vm/stdlib/bool.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::boolean_new>  (ReservedMemberCode::NEW),
		wrap<stdlib::boolean_is>   (ReservedMemberCode::IS),
		wrap<stdlib::boolean_cast> (ReservedMemberCode::CAST),
	};



	Value BoolType::get_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(static_functions, id).value_or(value::null);
	}
}