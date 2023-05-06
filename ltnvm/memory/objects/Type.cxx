#include "Type.hxx"
#include "ltn/type_code.hxx"
#include "ltnvm/Exception.hxx"

namespace ltn::vm {
	std::string to_type_name(const std::uint8_t * code) {
		switch (*code) {
		case type_code::ANY: return "...";
		case type_code::NVLL: return "null";
		case type_code::BOOL: return "bool";
		case type_code::CHAR: return "char";
		case type_code::INT: return "int";
		case type_code::FLOAT: return "float";
		case type_code::STRING: return "string";
		case type_code::ARRAY: return "array(" + to_type_name(std::next(code)) + ")";
		}
		throw except::invalid_argument("Cannot generate type name");
	}



	std::string to_type_name(const Type & type) {
		return to_type_name(type.code.data());	
	}
}