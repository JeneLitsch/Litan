#pragma once
#include "ltnvm/VMCore.hxx"

namespace ltn::vm::build_in {
	Value min(VMCore & core);
	Value max(VMCore & core);
	Value clamp(VMCore & core);

	Value round(VMCore & core);
	Value floor(VMCore & core);
	Value ceil(VMCore & core);

	Value abs(VMCore & core);

	Value sin(VMCore & core);
	Value cos(VMCore & core);
	Value tan(VMCore & core);

	Value sqrt(VMCore & core);
	Value hypot(VMCore & core);

	Value log(VMCore & core);
	Value ln(VMCore & core);
	Value ld(VMCore & core);
	Value lg(VMCore & core);
}