#include "cast_static.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/type/check.hxx"

namespace ltn::c {
	namespace {
		std::vector<std::uint8_t> to_type_code(	
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_bool(to)) {
				return { type_code::BOOL };
			}
		}
	}

	InstructionBuffer cast_static(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		return { inst::cast(to_type_code(from, to, location)) };
	}
}