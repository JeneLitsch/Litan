#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <span>

namespace ltn::c::compile {
	std::span<const std::string_view> resolve_build_in(const std::string_view & key);
}