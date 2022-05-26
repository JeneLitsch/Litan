#pragma once
#include "instructions.hxx"
#include "scan.hxx"
namespace ltn::a {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions,
		const AddressTable & jump_table);
}