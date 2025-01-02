#include "FloatType.hxx"
#include "litan_vm/stdlib/float.hxx"

namespace ltn::vm {
	static NativeFunctionTable static_functions {
		wrap<stdlib::floating_new>  (ReservedMemberCode::NEW),
		wrap<stdlib::floating_is>   (ReservedMemberCode::IS),
		wrap<stdlib::floating_cast> (ReservedMemberCode::CAST),
	};



	Value FloatType::get_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(static_functions, id).value_or(value::null);
	}
}