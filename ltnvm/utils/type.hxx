#pragma once
#include "ltnvm/objects/Type.hxx"

namespace ltn::vm {
	struct VmCore;
	std::pair<std::uint64_t, const std::uint8_t*> make_type(VmCore & core, const std::uint8_t * code);
}