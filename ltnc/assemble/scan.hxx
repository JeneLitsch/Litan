#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include "ltnc/inst/instructions.hxx"

namespace ltn::c {
	using AddressTable = std::unordered_map<std::string, std::uint64_t>;

	AddressTable scan(const std::vector<inst::Instruction> & instructions);
}