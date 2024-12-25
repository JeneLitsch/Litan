#include "String.hxx"
#include "stdxx/string.hxx"
#include "litan_vm/stdlib/string.hxx"
#include "litan_core/utf8.hxx"

namespace ltn::vm {
	String::String(std::string str, Encoding encoding) 
		: Object{}
		, storage {str}
		, str{*storage}
		, encoding { encoding }
		, character_count { utf8::character_count(str) }
		{}
	


	String::String(const String & string)
		: Object { string }
		, encoding { string.encoding }
		, character_count { string.character_count } {
		if (string.storage) {
			storage = string.storage;
			str = storage.value();
		}
		else {
			str = string.str;
		}
	}



	String::String(NonOwning, std::string_view string, Encoding encoding)
		: Object {}
		, storage{std::nullopt}
		, str{string}
		, encoding { encoding }
		, character_count { utf8::character_count(str) }
		{}



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
			wrap<stdlib::string_size>     (ReservedMemberCode::SIZE),
			wrap<stdlib::string_is_empty> (ReservedMemberCode::IS_EMTPY),
			wrap<stdlib::string_split>    (ReservedMemberCode::SPLIT),
		};
		return search_native_function_table(native_function_table, id);
	}



	bool String::empty() const {
		return std::empty(str);
	}



	std::uint32_t String::unsafe_back() const {
		return at(size() - 1);
	}



	std::uint32_t String::back() const {
		return at(size() - 1);
	}



	std::uint32_t String::unsafe_front() const {
		return at(0);
	}



	std::uint32_t String::front() const {
		return at(0);
	}



	std::uint32_t String::at(std::int64_t i) const {
		switch (encoding) {
		case Encoding::UTF8:
			return utf8::code_point_at(str, static_cast<std::size_t>(i));
		case Encoding::ASCII:
			return static_cast<std::uint32_t>(str[0]);
		}
	}



	std::int64_t String::size() const {
		return static_cast<std::int64_t>(character_count);
	}


	std::string String::copy_to_std_string() const {
		if(storage) {
			return storage.value();
		}
		else {
			return std::string{str};
		}
	}


	std::partial_ordering operator<=>(const String & l, const String & r) {
		return l.str <=> r.str;
	}
}