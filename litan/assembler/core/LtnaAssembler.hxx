#pragma once
#include <vector>
#include <string>
#include <map>
#include "LtnInstructions.hxx"
#include "LtnaTokenPackage.hxx"
#include "LtnaMarkerTable.hxx"
namespace ltn::a {
	class Assembler {
	public:
		// Assembles written Assembly code to a list of 64-Bit instructions
		std::vector<std::uint64_t> assemble(const std::vector<TokenPackage> & tokens);
	};
}