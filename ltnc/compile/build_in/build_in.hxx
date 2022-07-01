#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <span>
#include "ltn/InstructionSet.hxx"

namespace ltn::c {
	std::span<const ltn::inst::Instruction> resolve_build_in(const std::string_view & key);
}