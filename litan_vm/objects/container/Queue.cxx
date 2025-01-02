#include "Queue.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/queue.hxx"

namespace ltn::vm {
	void Queue::stringify(VMCore & core, std::ostream & oss, bool) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}



	Value Queue::get_member(VMCore & core, std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::queue_size>     (ReservedMemberCode::SIZE),
			wrap<stdlib::queue_is_empty> (ReservedMemberCode::IS_EMTPY),
			wrap<stdlib::queue_push>     (ReservedMemberCode::PUSH),
			wrap<stdlib::queue_pop>      (ReservedMemberCode::POP),
			wrap<stdlib::queue_values>   (ReservedMemberCode::VALUES),
		};
		return search_native_function_table(native_function_table, id).value_or(value::null);
	}
}