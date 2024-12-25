#include "OStream.hxx"

namespace ltn::vm {
	void OStream::stringify(VMCore &, std::ostream & oss, bool) {
		if(this->oss) {
			oss << this->oss->str();
		}
		else {
			oss << "<ostream>";
		}
		return;
	}
}