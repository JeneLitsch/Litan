#include "Queue.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm {
	void Queue::stringify(VMCore & core, std::ostream & oss, bool nested) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}
}