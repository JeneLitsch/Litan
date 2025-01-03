#include "StackType.hxx"
#include "litan_vm/stdlib/stack.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::stack_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::stack_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::stack_push>     (ReservedMemberCode::PUSH),
		wrap<stdlib::stack_pop>      (ReservedMemberCode::POP),
		wrap<stdlib::stack_values>   (ReservedMemberCode::VALUES),
	};



	static NativeFunctionTable static_functions {
		wrap<stdlib::stack_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::stack_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::stack_is>       (ReservedMemberCode::IS),
	};



	Value StackType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value StackType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}