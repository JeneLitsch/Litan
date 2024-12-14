#include "Stack.hxx"
#include "ltnvm/utils/stringify.hxx"
#include "ltnvm/stdlib/stack.hxx"

namespace ltn::vm {
	void Stack::stringify(VMCore & core, std::ostream & oss, bool nested) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}

	Value Stack::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::stack_size>     (MemberCode::SIZE),
			wrap<stdlib::stack_is_empty> (MemberCode::IS_EMTPY),
			wrap<stdlib::stack_push>     (MemberCode::PUSH),
			wrap<stdlib::stack_pop>      (MemberCode::POP),
		};
		return search_native_function_table(native_function_table, id);
	}
}