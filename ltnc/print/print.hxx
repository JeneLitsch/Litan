#pragma once
#include <span>
#include "ltn/InstructionSet.hxx"

namespace ltn::c {
	std::string print(const std::span<const inst::Instruction> & instructions);
}