#include "Stack.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/stack.hxx"

namespace ltn::vm {
	void Stack::stringify(VMCore & core, std::ostream & oss, bool) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}

	Value Stack::get_member(VMCore & core, std::uint64_t id) const {
		return core.types.stack.get_nonstatic_member(core, id);
	}
}