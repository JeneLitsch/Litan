#include "IStream.hxx"

namespace ltn::vm {
	void IStream::stringify(VMCore &, std::ostream & oss, bool) {
		oss << "<istream>";
	}
}