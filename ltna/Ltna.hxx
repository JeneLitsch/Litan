#pragma once
#include <vector>
#include <cstdint>
#include <istream>
#include "ltn/InstructionSet.hxx"

namespace ltn::a {
	std::vector<std::uint8_t> assemble(std::istream & in);
	std::vector<std::uint8_t> assemble(const std::vector<inst::Instruction> & instructions);
}