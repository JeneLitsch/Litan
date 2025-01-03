#include "StackType.hxx"
#include "litan_vm/stdlib/queue.hxx"

namespace ltn::vm {
	static NativeFunctionTable nonstatic_functions {
		wrap<stdlib::queue_size>     (ReservedMemberCode::SIZE),
		wrap<stdlib::queue_is_empty> (ReservedMemberCode::IS_EMTPY),
		wrap<stdlib::queue_push>     (ReservedMemberCode::PUSH),
		wrap<stdlib::queue_pop>      (ReservedMemberCode::POP),
		wrap<stdlib::queue_values>   (ReservedMemberCode::VALUES),
	};



	static NativeFunctionTable static_functions {
		wrap<stdlib::queue_new>      (ReservedMemberCode::NEW),
		wrap<stdlib::queue_cast>     (ReservedMemberCode::CAST),
		wrap<stdlib::queue_is>       (ReservedMemberCode::IS),
	};



	Value QueueType::get_member(VMCore & core, std::uint64_t id) const {
		if(auto member = search_native_function_table(static_functions, id)) {
			return member.value();
		}
		return get_nonstatic_member(core, id);
	}



	Value QueueType::get_nonstatic_member(VMCore & core, std::uint64_t id) const {
		return search_native_function_table(nonstatic_functions, id).value_or(value::null);
	}
}