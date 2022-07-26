#pragma once
#include "ltnc/inst/instructions.hxx"
#include "scan.hxx"
#include <unordered_map>

namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions,
		const AddressTable & jump_table,
		const std::unordered_map<std::string, std::uint64_t> & fx_table = {});
}