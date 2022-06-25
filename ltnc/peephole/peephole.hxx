#pragma once

#include "ltn/InstructionSet.hxx"

namespace ltn::c::peephole {
	std::vector<ltn::inst::Instruction> optimize(
		const std::vector<ltn::inst::Instruction> & input);
}