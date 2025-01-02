#include "IntType.hxx"
#include "litan_vm/stdlib/int.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::integer_new>  (ReservedMemberCode::NEW),
		wrap<stdlib::integer_is>   (ReservedMemberCode::IS),
		wrap<stdlib::integer_cast> (ReservedMemberCode::CAST),
	};



	Value IntType::get_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(static_functions, id).value_or(value::null);
	}
}