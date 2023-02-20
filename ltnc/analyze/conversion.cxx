#include <sstream>
#include "conversion.hxx"
#include "ltnc/type/traits.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/analyze/error.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr make_static_cast(sst::expr_ptr from, const type::Type & type) {
			return std::make_unique<sst::TypedUnary>(
				sst::TypedUnary::Op::STATIC_CAST,
				type,
				std::move(from),
				type
			);
		}



		sst::expr_ptr generate_conversion(sst::expr_ptr from, const type::Type & to) {
			if(is_bool(to))  return make_static_cast(std::move(from), to);
			if(is_char(to))  return make_static_cast(std::move(from), to);
			if(is_int(to))   return make_static_cast(std::move(from), to);
			if(is_float(to)) return make_static_cast(std::move(from), to);
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
			else return is_convertible(from, to.as<type::Optional>()->contains);
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
			throw cannot_assign(location, from->type, to);
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
			throw cannot_pass(location, from->type, to);
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
			throw cannot_return(location, from->type, to);
		}
		
	}
}