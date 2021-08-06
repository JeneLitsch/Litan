#pragma once
#include <vector>
#include <string>
#include <map>
#include "LtnInstructions.hxx"
#include "LtnaTokenPackage.hxx"
#include "LtnaMarkerTable.hxx"
namespace ltna {
	class Assembler {
	public:
		std::vector<std::uint64_t> assemble(const std::vector<TokenPackage> & tokens);
	};
}