#include "Queue.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/queue.hxx"

namespace ltn::vm {
	void Queue::stringify(VMCore & core, std::ostream & oss, bool nested) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}



	Value Queue::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::queue_size>     (MemberCode::SIZE),
			wrap<stdlib::queue_is_empty> (MemberCode::IS_EMTPY),
			wrap<stdlib::queue_push>     (MemberCode::PUSH),
			wrap<stdlib::queue_pop>      (MemberCode::POP),
			wrap<stdlib::queue_values>   (MemberCode::VALUES),
		};
		return search_native_function_table(native_function_table, id);
	}
}