#pragma once
#include "objects/Type.hxx"

namespace ltn::vm {
	struct VmCore;
	std::pair<const TypeNode*, const std::uint8_t*> make_type(VmCore & core, const std::uint8_t * code);
}