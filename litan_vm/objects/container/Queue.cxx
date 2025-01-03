#include "Queue.hxx"
#include "litan_vm/utils/stringify.hxx"
#include "litan_vm/stdlib/queue.hxx"

namespace ltn::vm {
	void Queue::stringify(VMCore & core, std::ostream & oss, bool) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}



	Value Queue::get_member(VMCore & core, std::uint64_t id) const {
		return core.types.queue.get_nonstatic_member(core, id);
	}
}