#pragma once
#include "Assembler.hxx"
#include "PseudoAssembler.hxx"
#include "AssemblerParser.hxx"
namespace ltna {
	class Ltna {
	public:
		std::vector<std::uint64_t> assemble(const std::string & assembly) const;
	};
}