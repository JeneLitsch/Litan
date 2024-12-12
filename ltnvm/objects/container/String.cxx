#include "String.hxx"
#include "stdxx/string.hxx"

namespace ltn::vm {
	void String::stringify(VMCore &, std::ostream & oss, bool nested) {
		if (nested) {
			oss << '"';
			for (char c : this->data) {
				switch (c) {
				case '\n': oss << "\\n"; break;
				case '\t': oss << "\\t"; break;
				case '\\': oss << "\\\\"; break;
				case '"': oss << "\\\""; break;
				default: oss << c;
				}
			}
			oss << '"';
		}
		else {
			oss << this->data;
		}
	}
}