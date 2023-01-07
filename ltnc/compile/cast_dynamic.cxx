#include "cast_dynamic.hxx"
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

			if(type::is_char(to)) {
				return { type_code::CHAR };
			}

			if(type::is_int(to)) {
				return { type_code::INT };
			}

			if(type::is_float(to)) {
				return { type_code::FLOAT };
			}

			if(type::is_string(to)) {
				return { type_code::STRING };
			}

			if(type::is_array(to)) {
				auto * arr = to.as<type::Array>();
				return to_array_of(to_type_code(from, **arr->contains, location));
			}

			throw cannot_cast(from, to, location);
		}
	}



	InstructionBuffer cast_dynamic(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(type::is_any(to)) return {};
		return { inst::safe_cast(to_type_code(from, to, location)) };
	}
}