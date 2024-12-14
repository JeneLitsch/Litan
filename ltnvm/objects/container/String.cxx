#include "String.hxx"
#include "stdxx/string.hxx"
#include "ltnvm/stdlib/string.hxx"

namespace ltn::vm {
	void String::stringify(VMCore &, std::ostream & oss, bool nested) {
		if (nested) {
			oss << '"';
			for (char c : this->str) {
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
			oss << this->str;
		}
	}



	Value String::get_member(std::uint64_t id) const {
		static NativeFunctionTable native_function_table {
			wrap<stdlib::string_size>     (MemberCode::SIZE),
			wrap<stdlib::string_is_empty> (MemberCode::IS_EMTPY),
		};
		return search_native_function_table(native_function_table, id);
	}
}