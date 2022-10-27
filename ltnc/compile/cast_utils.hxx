#pragma once
#include "ltnc/SourceLocation.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/CompilerError.hxx"
#include "ltnc/compile/utils/ExprResult.hxx"

namespace ltn::c {
	CompilerError cannot_cast(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location);

	std::vector<std::uint8_t> to_array_of(const std::vector<std::uint8_t> & subtype_code);
}