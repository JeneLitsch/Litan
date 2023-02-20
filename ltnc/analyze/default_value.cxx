#include "default_value.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/type/traits.hxx"
#include "ltnc/type/to_string.hxx"

namespace ltn::c {
	auto default_any(const type::Type & type) {
		return std::make_unique<sst::Null>(type); 
	}



	auto default_optional(const type::Type & type) {
		return std::make_unique<sst::Null>(type); 
	}


	
	auto default_bool(const type::Type & type) {
		return std::make_unique<sst::Bool>(false, type);
	}


	
	auto default_int(const type::Type & type) {
		return std::make_unique<sst::Integer>(0, type);
	}



	auto default_float(const type::Type & type) {
		return std::make_unique<sst::Float>(0.0, type);
	}



	auto default_string(const type::Type & type) {
		return std::make_unique<sst::String>("", type);
	}
	


	auto default_array(const type::Type & type) {
		return std::make_unique<sst::Array>(type);
	}
	


	sst::expr_ptr generate_default_value(
		const type::Type & type,
		const SourceLocation & location) {
		if(type::is_any(type))      return default_any(type);
		if(type::is_optional(type)) return default_optional(type);
		if(type::is_bool(type))     return default_bool(type); 
		if(type::is_int(type))      return default_int(type); 
		if(type::is_float(type))    return default_float(type);
		if(type::is_string(type))   return default_string(type);
		if(type::is_array(type))    return default_array(type);
		throw CompilerError {
			"Cannot default initialize type " + type::to_string(type),
			location
		};
	}
}