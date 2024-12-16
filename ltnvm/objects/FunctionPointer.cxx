#include "FunctionPointer.hxx"

namespace ltn::vm {
	void FunctionPointer::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<function>";
	}
}