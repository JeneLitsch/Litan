#pragma once
#include "ltnvm/VmCore.hxx"

namespace ltn::vm::build_in {
	Value min(VmCore & core);
	Value max(VmCore & core);
	Value clamp(VmCore & core);

	Value round(VmCore & core);
	Value floor(VmCore & core);
	Value ceil(VmCore & core);
}