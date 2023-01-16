#include "traits.hxx"
#include "stdxx/functional.hxx"

namespace ltn::c::type {
	namespace {
		bool all_types(const Type &) {
			return true;
		}



		bool is_subtype(auto condition, const type::Type & to) {
			if(auto arr = to.as<type::Array>()) return condition(*arr->contains);
			return false;
		}



		bool are_subtypes(auto condition, const type::Type & from, const type::Type & to) {
			auto arr_from = from.as<type::Array>();
			auto arr_to = to.as<type::Array>();
			if(arr_from && arr_to) return condition(
				*arr_from->contains,
				*arr_to->contains
			);
			return false;
		}
	}



	bool is_static_castable(const Type & from, const Type & to) {
		if(all_types(from)      && is_any(to))         return true;
		if(all_types(from)      && is_bool(to))        return true;
		if(is_numeric(from)     && is_numeric(to))     return true;
		if(is_empty_array(from) && is_array(to))       return true;
		if(is_array(from)       && is_empty_array(to)) return false;
		if(is_array(from)       && is_array(to)) {
			return are_subtypes(std::equal_to<>{}, from, to);
		}
		return false;
	}




	bool is_dynamic_castable(const Type & to) {
		if(is_any(to))    return true;
		if(is_bool(to))   return true;
		if(is_char(to))   return true;
		if(is_int(to))    return true;
		if(is_float(to))  return true;
		if(is_string(to)) return true;
		if(is_array(to))  return is_subtype(is_dynamic_castable, to);
		return false;
	}



	bool is_static_copyable(const Type & from, const Type & to) {
		if(all_types(from)        && is_bool(to))          return true;
		if(is_numeric(from)       && is_char(to))          return true;
		if(is_numeric(from)       && is_int(to))           return true;
		if(is_numeric(from)       && is_float(to))         return true;
		if(is_numeric_array(from) && is_string(to))        return true;
		if(is_empty_array(from)   && is_string(to))        return true;
		if(is_string(from)        && is_string(to))        return true;
		if(is_string(from)        && is_numeric_array(to)) return true;
		if(is_empty_array(from)   && is_array(to))         return true;
		if(is_array(from)         && is_empty_array(to))   return false;
		if(is_array(from)         && is_array(to)) {
			return are_subtypes(is_static_copyable, from, to);
		} 
		return false;
	}



	bool is_dynamic_copyable(const Type & to) {
		if(is_any(to))    return true;
		if(is_bool(to))   return true;
		if(is_char(to))   return true;
		if(is_int(to))    return true;
		if(is_float(to))  return true;
		if(is_string(to)) return true;
		if(is_array(to))  return is_subtype(is_dynamic_copyable, to);
		return false;
	}
}