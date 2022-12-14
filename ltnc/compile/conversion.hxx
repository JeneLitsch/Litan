#pragma once
#include "ltnc/SourceLocation.hxx"
#include "ltnc/compile/utils/InstructionBuffer.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/sst/SST.hxx"

namespace ltn::c {
	sst::expr_ptr conversion_on_assign(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location);

	sst::expr_ptr conversion_on_pass(
		sst::expr_ptr from,
		const type::Type & to,
		const ArgumentLocation & location);

	sst::expr_ptr conversion_on_return(
		sst::expr_ptr from,
		const type::Type & to,
		const SourceLocation & location);
}