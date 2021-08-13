#pragma once
#include "LtnaAssembler.hxx"
#include "LtnaPseudoAssembler.hxx"
#include "LtnaAssemblerParser.hxx"

namespace ltn::a {
	class Ltna {
	public:
		std::vector<std::uint64_t> assemble(const std::string & assembly);
		void registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct);
	private:
		AssemblerParser assemblerParser;
		PseudoAssembler pseudoAssembler;
		Assembler assembler;
	};
}