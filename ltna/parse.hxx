#pragma once
#include "instructions.hxx"
#include <istream>
namespace ltn::a {
	std::vector<inst::Instruction> parse(std::istream & in);
}