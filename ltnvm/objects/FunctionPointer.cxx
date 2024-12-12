#include "FunctionPointer.hxx"

namespace ltn::vm {
	void FunctionPointer::stringify(VMCore & core, std::ostream & oss, bool nested) {
		oss << "<function>";
	}
}