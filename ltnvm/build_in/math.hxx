#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value min(VmCore & core);
	Value max(VmCore & core);
	Value clamp(VmCore & core);

	Value round(VmCore & core);
	Value floor(VmCore & core);
	Value ceil(VmCore & core);

	Value abs(VmCore & core);

	Value sin(VmCore & core);
	Value cos(VmCore & core);
	Value tan(VmCore & core);

	Value sqrt(VmCore & core);
	Value hypot(VmCore & core);

	Value log(VmCore & core);
	Value ln(VmCore & core);
	Value ld(VmCore & core);
	Value lg(VmCore & core);
}