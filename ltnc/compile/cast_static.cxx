#include "cast_static.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/compile/cast_utils.hxx"

namespace ltn::c {
	namespace {

	}



	InstructionBuffer cast_static(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(type::is_any(to)) return {};
		return { inst::cast(type::encode_type(to)) };
	}
}