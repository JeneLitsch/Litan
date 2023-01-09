#include "cast_static.hxx"
#include "ltn/type_code.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/compile/cast_utils.hxx"

namespace ltn::c {
	namespace {
		bool is_castable(const type::Type & from, const type::Type & to) {
			if(type::is_bool(to)) return true;
			if(type::is_numeric(from) && type::is_char(to)) return true;
			if(type::is_numeric(from) && type::is_int(to)) return true;
			if(type::is_numeric(from) && type::is_float(to)) return true;
			if(type::is_empty_array(from) && type::is_array(to)) return true;
			return false;
		}
	}



	InstructionBuffer cast_static(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(type::is_any(to)) return {};
		if(is_castable(from, to)) {
			return { inst::cast(type::encode_type(to)) };
		}
		else {
			throw cannot_cast(from, to, location);
		}
	}
}