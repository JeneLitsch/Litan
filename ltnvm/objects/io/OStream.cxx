#include "OStream.hxx"

namespace ltn::vm {
	void OStream::stringify(VMCore & core, std::ostream & oss, bool nested) {
		if(this->oss) {
			oss << this->oss->str();
		}
		else {
			oss << "<ostream>";
		}
		return;
	}
}