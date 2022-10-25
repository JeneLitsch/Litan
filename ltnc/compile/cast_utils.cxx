#include <sstream>
#include "stdxx/array.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/compile/cast_utils.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
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
}