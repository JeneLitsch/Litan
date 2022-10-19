#include <sstream>
#include "conversion.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		InstructionBuffer conversion_on_copy(
			const type::Type & from,
			const type::Type & to,
			const auto & on_error) {

			if(type::is_any(to))                  return {};
			if(to == from)                        return {};
			if(is_bool(to))                       return { inst::CastFloat{} };
			if(is_char(to)  && is_subint(from))   return { inst::CastChar{}  };
			if(is_int(to)   && is_integral(from)) return { inst::CastInt{}   };
			if(is_float(to) && is_numeric(from))  return { inst::CastFloat{} };
			if(is_subtype_array(from, to))        return {};
			
			on_error();
			return {};
		}
	}

	InstructionBuffer conversion_on_assign(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {

		return conversion_on_copy(from, to, [&] {
			std::ostringstream oss;
			oss << "Cannot assign " << from << " to "<< to;
			throw CompilerError{oss.str(), location};
		});
	}



	InstructionBuffer conversion_on_modify(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		
		// Special cases for char incrementation
		if(type::is_any(to))                 return {};
		if(to == from)                       return {};

		std::ostringstream oss;
		oss << "Cannot assign " << from << " to "<< to;
		throw CompilerError{oss.str(), location};
	}



	InstructionBuffer conversion_on_pass(
		const type::Type & from,
		const type::Type & to,
		const ArgumentLocation & location) {
		
		return conversion_on_copy(from, to, [&] {
			std::ostringstream oss;
			oss << "Cannot pass " << from << " as " << to << " for argument " << location.index+1;
			throw CompilerError{oss.str(), location.source_location};
		});
	}



	InstructionBuffer conversion_on_return(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		
		return conversion_on_copy(from, to, [&] {
			std::ostringstream oss;
			oss << "Cannot return " << from << " as "<< to;
			throw CompilerError{oss.str(), location};
		});
	}
}