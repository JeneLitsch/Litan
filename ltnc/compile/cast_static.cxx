#include "cast_static.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/compile/cast_utils.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> to_type_code(	
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_bool(to)) {
				return { type_code::BOOL };
			}

			if(type::is_numeric(from) && type::is_char(to)) {
				return { type_code::CHAR };
			}

			if(type::is_numeric(from) && type::is_int(to)) {
				return { type_code::INT };
			}

			if(type::is_numeric(from) && type::is_float(to)) {
				return { type_code::FLOAT };
			}

			throw cannot_cast(from, to, location);
		}
	}

	InstructionBuffer cast_static(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		return { inst::cast(to_type_code(from, to, location)) };
	}
}