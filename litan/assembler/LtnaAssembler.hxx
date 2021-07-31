#pragma once
#include "LtnInstructions.hxx"
#include <vector>
#include <string>
#include <map>
#include "LtnaAssemblerParser.hxx"
#include "LtnaPseudoAssembler.hxx"
#include "LtnaTokenPackage.hxx"
#include "LtnHeapTypes.hxx"
#include "LtnIoFormat.hxx"
namespace ltna {
	class Assembler {
	public:
		std::vector<std::uint64_t> assemble(const std::vector<TokenPackage> & tokens);
		void registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct);
	private:
		void searchMarkers(const std::vector<TokenPackage> & lines);
		void assembleLine(const TokenPackage & tokenPackages);

		// command format
		void cFormat(InstCode opcode);
		// functioncode format
		void fFormat(InstCode opcode, std::uint8_t funct);
		void fFormat(InstCode opcode, ltn::HeapType type);
		void fFormat(InstCode opcode, ltn::OuputFormat format);
		// value format with 32bit parameter
		void vFormat(InstCode opcode, std::uint32_t val);
		// jump format with 56bit parameter
		void jFormat(InstCode opcode, const std::string & destination);
		
		void dFormat(InstCode opcode, std::uint64_t arg56);
		void dFormat(const std::vector<std::string> & stringData);
	
		std::vector<std::uint64_t> instructions;
		PseudoAssembler pseudoAssembler;
		std::map<std::string, std::uint64_t> markers;
	};
}