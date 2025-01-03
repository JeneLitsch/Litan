#include "ClockType.hxx"
#include "litan_vm/stdlib/chrono.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::to_seconds>      (ReservedMemberCode::TO_SECONDS),
		wrap<stdlib::to_milliseconds> (ReservedMemberCode::TO_MILLISECONDS),
	};


	static NativeFunctionTable static_functions {
		wrap<stdlib::clock_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::clock_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::clock_is>       (ReservedMemberCode::IS),
	};



	Value ClockType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value ClockType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}