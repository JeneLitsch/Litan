#include "RandomEngineType.hxx"
#include "litan_vm/stdlib/random.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {};


	static NativeFunctionTable static_functions {
		wrap<stdlib::rng_cast> (ReservedMemberCode::CAST),
		wrap<stdlib::rng_is>   (ReservedMemberCode::IS),
	};



	Value RandomEngineType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value RandomEngineType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}