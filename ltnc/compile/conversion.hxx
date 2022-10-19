#pragma once
#include "ltnc/SourceLocation.hxx"
#include "ltnc/compile/utils/InstructionBuffer.hxx"
#include "ltnc/type/Type.hxx"

namespace ltn::c {
	InstructionBuffer conversion_on_assign(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location);

	InstructionBuffer conversion_on_modify(
		const type::Type & from,
		const type::Type & to,
		const SourceLocation & location);

	InstructionBuffer conversion_on_pass(
		const type::Type & from,
		const type::Type & to,
		const ArgumentLocation & location);
}