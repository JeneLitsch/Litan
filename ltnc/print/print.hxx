#pragma once
#include <span>
#include "ltnc/inst/instructions.hxx"

namespace ltn::c {
	std::string print(const std::span<const inst::Instruction> & instructions);
}