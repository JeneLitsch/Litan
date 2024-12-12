#include "IStream.hxx"

namespace ltn::vm {
	void IStream::stringify(VMCore & core, std::ostream & oss, bool nested) {
		oss << "<istream>";
	}
}