#include <sstream>
#include "conversion.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr generate_conversion(
			sst::expr_ptr from,
			const type::Type & to) {

			if(type::is_any(to)) return from;
			if(to == from->type) return from;
			if(is_bool(to))   return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_char(to))   return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_int(to))    return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_float(to))  return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_optional(to)) {
				if(is_null(from->type)) return from;
				else {
					return generate_conversion(std::move(from), *to.as<type::Optional>()->contains);
				}
			}
			
			return from;
		}
	}
	
	

	bool is_convertible(
		const type::Type & from,
		const type::Type & to) {
		if(type::is_any(to))                  return true;
		if(to == from)                        return true;
		if(is_bool(to))                       return true;
		if(is_char(to)  && is_subint(from))   return true;
		if(is_int(to)   && is_integral(from)) return true;
		if(is_float(to) && is_numeric(from))  return true;
		if(is_subtype_array(from, to))        return true;
		if(is_optional(to)) {
			if(is_null(from)) return true;
			else return is_convertible(from, *to.as<type::Optional>()->contains);
		}
		
		return false;
	}



	sst::expr_ptr conversion_on_assign(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location) {

		if(is_convertible(from->type, to)) {
			return generate_conversion(std::move(from), to);
		}
		else {
			std::ostringstream oss;
			oss << "Cannot assign " << from->type << " to "<< to;
			throw CompilerError{oss.str(), location};
		}
	}







	sst::expr_ptr conversion_on_pass(
		sst::expr_ptr from,
		const type::Type & to,
		const ArgumentLocation & location) {
		if(is_convertible(from->type, to)) {
			return generate_conversion(std::move(from), to);
		}
		else {
			std::ostringstream oss;
			oss << "Cannot pass " << from->type << " as " << to << " for argument " << location.index+1;
			throw CompilerError{oss.str(), location.source_location};
		}
	}



	sst::expr_ptr conversion_on_return(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location) {

		if(is_convertible(from->type, to)) {
			return generate_conversion(std::move(from), to);
		}
		else {
			std::ostringstream oss;
			oss << "Cannot return " << from->type << " as "<< to;
			throw CompilerError{oss.str(), location};
		}
	}
}