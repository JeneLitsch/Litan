#pragma once
#include "ltnc/sst/SST.hxx"
#include "ltnc/type/Type.hxx"
#include "ltnc/SourceLocation.hxx"

namespace ltn::c {
	sst::expr_ptr generate_default_value(
		const type::Type & type,
		const SourceLocation & location);
}