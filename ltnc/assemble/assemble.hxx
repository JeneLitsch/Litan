#pragma once
#include "ltnc/inst/instructions.hxx"
#include "ltnc/AddressTable.hxx"
#include "scan.hxx"

namespace ltn::c {
	std::vector<std::uint8_t> assemble(
		const std::vector<inst::Instruction> & instructions,
		const AddressTable & jump_table,
		const AddressTable & fx_table,
		const AddressTable & static_table);
}