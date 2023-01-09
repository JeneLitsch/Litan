#pragma once
#include "Type.hxx"

namespace ltn::c::type {
	std::vector<std::uint8_t> encode_type(const Type & type);
}