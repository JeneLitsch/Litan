#include "encode.hxx"
#include "stdxx/array.hxx"
#include "ltn/type_code.hxx"
#include "check.hxx"
#include "to_string.hxx"

namespace ltn::c::type {
	namespace {
		std::vector<std::uint8_t> array_of(const std::vector<std::uint8_t> & subtype_code) {
			std::vector<std::uint8_t> type_code;
			type_code += ltn::type_code::ARRAY;
			type_code += subtype_code;
			return type_code; 
		}	
	}

	std::vector<std::uint8_t> encode_type(const Type & type) {
		if(type::is_bool(type)) {
			return { type_code::BOOL };
		}

		if(type::is_char(type)) {
			return { type_code::CHAR };
		}

		if(type::is_int(type)) {
			return { type_code::INT };
		}

		if(type::is_float(type)) {
			return { type_code::FLOAT };
		}

		if(type::is_string(type)) {
			return { type_code::STRING };
		}

		if(type::is_array(type)) {
			auto * arr = type.as<type::Array>();
			return array_of(encode_type(**arr->contains));
		}

		throw std::runtime_error{"Cannot encode type: " + to_string(type)};
	}
}