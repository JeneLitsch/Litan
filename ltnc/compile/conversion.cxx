#include <sstream>
#include "conversion.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		sst::expr_ptr conversion_on_copy(
			sst::expr_ptr from,
			const type::Type & to,
			const auto & on_error) {

			if(type::is_any(to))                  return from;
			if(to == from)                        return from;
			if(is_bool(to))                       return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_char(to)  && is_subint(from))   return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_int(to)   && is_integral(from)) return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_float(to) && is_numeric(from))  return std::make_unique<sst::TypedUnary>(sst::TypedUnary::Op::STATIC_CAST, to, std::move(from), to);
			if(is_subtype_array(from, to))        return from;
			if(is_optional(to)) {
				if(is_null(from)) return from;
				else return conversion_on_copy(from, *to.as<type::Optional>()->contains, on_error);
			}
			
			on_error();
			return from;
		}
	}

	sst::expr_ptr conversion_on_assign(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location) {
		const auto from_type = from->type;

		return conversion_on_copy(std::move(from), to, [&] {
			std::ostringstream oss;
			oss << "Cannot assign " << from_type << " to "<< to;
			throw CompilerError{oss.str(), location};
		});
	}







	sst::expr_ptr conversion_on_pass(
		sst::expr_ptr from,
		const type::Type & to,
		const ArgumentLocation & location) {
		const auto from_type = from->type;
		
		return conversion_on_copy(std::move(from), to, [&] {
			std::ostringstream oss;
			oss << "Cannot pass " << from_type << " as " << to << " for argument " << location.index+1;
			throw CompilerError{oss.str(), location.source_location};
		});
	}



	sst::expr_ptr conversion_on_return(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location) {
		const auto from_type = from->type;
		
		return conversion_on_copy(std::move(from), to, [&] {
			std::ostringstream oss;
			oss << "Cannot return " << from_type << " as "<< to;
			throw CompilerError{oss.str(), location};
		});
	}
}