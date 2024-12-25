#include "Object.hxx"

namespace ltn::vm {
	void Object::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<Object>";
	}
}