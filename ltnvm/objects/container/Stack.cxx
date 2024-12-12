#include "Stack.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm {
	void Stack::stringify(VMCore & core, std::ostream & oss, bool nested) {
		print_all(std::begin(this->data), std::end(this->data), oss, core, '<', '>');
	}
}