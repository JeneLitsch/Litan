#include "Coroutine.hxx"
#include "ltnvm/utils/stringify.hxx"

namespace ltn::vm {
	void Coroutine::stringify(VMCore & core, std::ostream & oss, bool nested) {
		oss << "<coroutine";
		print_all(std::begin(this->local_variables), std::end(this->local_variables), oss, core, '{', '}');
		oss << ">";
	}
}