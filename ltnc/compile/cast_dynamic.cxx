#include "cast_dynamic.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/type/encode.hxx"
#include "ltnc/compile/cast_utils.hxx"

namespace ltn::c {
	namespace {
		bool is_castable(const type::Type & from, const type::Type & to) {
			if(type::is_bool(to))   return true;
			if(type::is_char(to))   return true;
			if(type::is_int(to))    return true;
			if(type::is_float(to))  return true;
			if(type::is_string(to)) return true;
			if(type::is_array(to)) {
				return is_castable(from, **to.as<type::Array>()->contains);
			}
			return false;
		}
	}



	InstructionBuffer cast_dynamic(	
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(type::is_any(to)) return {};
		if(is_castable(from, to)) {
			return { inst::safe_cast(type::encode_type(to)) };
		}
		else {
			throw cannot_cast(from, to, location);
		}
	}
}