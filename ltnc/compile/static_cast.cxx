#include <sstream>
#include "ltnc/compile/static_cast.hxx"
#include "ltnc/type/check.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	namespace {
		CompilerError cannot_cast(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			std::ostringstream oss;
			oss << "Cannot static_cast " << from << " to " << to;
			return CompilerError{oss.str(), location};
		}



		InstructionBuffer cast_to_bool(
			const type::Type &,
			const type::Type &,
			const SourceLocation &) {
			
			return { inst::CastBool{} };
		}



		InstructionBuffer cast_to_char(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { inst::CastChar{} };
			throw cannot_cast(from, to, location);
		}



		InstructionBuffer cast_to_int(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { inst::CastInt{} };
			throw cannot_cast(from, to, location);
		}



		InstructionBuffer cast_to_float(
			const type::Type & from,
			const type::Type & to,
			const SourceLocation & location) {
			
			if(type::is_numeric(from)) return { inst::CastFloat{} };
			throw cannot_cast(from, to, location);
		}
	}



	InstructionBuffer cast_static(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location) {
		if(from == to) return {};
		if(type::is_bool(to))  return cast_to_bool(from, to, location);
		if(type::is_char(to))  return cast_to_char(from, to, location);
		if(type::is_int(to))   return cast_to_int(from, to, location);
		if(type::is_float(to)) return cast_to_float(from, to, location);
		throw cannot_cast(from, to, location);
	}
}