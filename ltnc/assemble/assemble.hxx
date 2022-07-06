#pragma once
#include "ltn/InstructionSet.hxx"
#include "scan.hxx"
namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions,
		const AddressTable & jump_table);
}