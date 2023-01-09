#include "cast_dynamic.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/compile/cast_utils.hxx"

namespace ltn::c {




	InstructionBuffer cast_dynamic(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		return { inst::safe_cast(type::encode_type(to)) };
	}
}