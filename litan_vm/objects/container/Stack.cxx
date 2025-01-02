#include "Stack.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/stack.hxx"

namespace ltn::vm {
	void Stack::stringify(VMCore & core, std::ostream & oss, bool) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}

	Value Stack::get_member(VMCore & core, std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::stack_size>     (ReservedMemberCode::SIZE),
			wrap<stdlib::stack_is_empty> (ReservedMemberCode::IS_EMTPY),
			wrap<stdlib::stack_push>     (ReservedMemberCode::PUSH),
			wrap<stdlib::stack_pop>      (ReservedMemberCode::POP),
			wrap<stdlib::stack_values>   (ReservedMemberCode::VALUES),
		};
		return search_native_function_table(native_function_table, id);
	}
}