#pragma once
#include "ltn/InstructionSet.hxx"
#include <istream>
namespace ltn::c {
	std::vector<inst::Instruction> parse(std::istream & in);
}