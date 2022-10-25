#include <sstream>
#include "stdxx/array.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/compile/static_cast.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		CompilerError cannot_cast(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			std::ostringstream oss;
			oss << "Cannot static_cast " << from << " to " << to;
			return CompilerError{oss.str(), location};
		}
	


		std::vector<std::uint8_t> to_array_of(const std::vector<std::uint8_t> & subtype_code) {
			std::vector<std::uint8_t> type_code;
			type_code += ltn::type_code::ARRAY;
			type_code += subtype_code;
			return type_code; 
		}



		std::vector<std::uint8_t> to_type_code(
			const type::Type &,
			const type::Type &,
			const SourceLocation &);



		std::vector<std::uint8_t> cast_to_bool(
			const type::Type &,
			const type::Type &,
			const SourceLocation &) {
			return { type_code::BOOL };
		}



		std::vector<std::uint8_t> cast_to_char(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { type_code::CHAR };
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to_int(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { type_code::INT };
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to_float(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { type_code::FLOAT };
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to_string(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {

			if(type::is_array(from)) {
				const auto & from_contained = from.as<type::Array>()->contains;
				
				if(!from_contained) return {
					type_code::STRING
				};

				if(type::is_numeric(**from_contained)) return {
					type_code::STRING
				};
			}
			
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> cast_to_array(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			const auto & to_array = *to.as<type::Array>();
			const auto & to_contained = **to_array.contains;
			
			if(type::is_array(from)) {
				// Allows casting empty array to any other array type
				const auto & from_contained 
					= from.as<type::Array>()->contains
					? **from.as<type::Array>()->contains
					: to_contained;

				return to_array_of(to_type_code(from_contained, to_contained, location)); 
			}
			if(type::is_string(from)) {
				if(type::is_numeric(to_contained)) {
					// Cast string like an array<char>
					return to_array_of(to_type_code(type::Char{}, to_contained, location)); 
				}
			}
			throw cannot_cast(from, to, location);
		}



		std::vector<std::uint8_t> to_type_code(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_bool(to))   return cast_to_bool(from, to, location);
			if(type::is_char(to))   return cast_to_char(from, to, location);
			if(type::is_int(to))    return cast_to_int(from, to, location);
			if(type::is_float(to))  return cast_to_float(from, to, location);
			if(type::is_string(to)) return cast_to_string(from, to, location);
			if(type::is_array(to))  return cast_to_array(from, to, location);
			throw cannot_cast(from, to, location);
		}
	}



	InstructionBuffer cast_static(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(from == to) return {};
		return { inst::Cast{ to_type_code(from, to, location) }};
	}
}