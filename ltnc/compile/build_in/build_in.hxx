#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <span>
#include <array>
#include "ltnc/inst/inst.hxx"

namespace ltn::c {
	std::span<const inst::Inst> resolve_build_in(const std::string_view & key);
}