#pragma once

#include "ltn/InstructionSet.hxx"

namespace ltn::c {
	std::vector<ltn::inst::Instruction> peephole(
		const std::vector<ltn::inst::Instruction> & input);
}