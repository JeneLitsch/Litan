#pragma once
#include "LtnInstructions.hxx"
#include <vector>
#include <string>
#include <map>
#include "AssemblerParser.hxx"
#include "PseudoAssembler.hxx"
#include "TokenPackage.hxx"
#include "LtnHeapTypes.hxx"
namespace ltn {
	class Assembler {
	public:
		std::vector<std::uint64_t> assemble(const std::vector<TokenPackage> & tokens);
		void registerAlias(const std::string & alias, Slot slot, std::uint8_t funct);
	private:
		void searchMarkers(const std::vector<TokenPackage> & lines);
		void assembleLine(const TokenPackage & tokenPackages);
		std::vector<std::uint64_t> instructions;
		std::string decodeString(const std::vector<std::string> & args) const;

		// convert to int depending on prefix
		static std::uint32_t toInt32(const std::string & str);
		static std::uint64_t toInt64(const std::string & str);

		// command format
		void cFormat(InstCode code);
		// buffer format
		void fFormat(InstCode code, std::uint8_t funct);
		void fFormat(InstCode code, HeapType type);
		// value format with 32bit parameter
		void vFormat(InstCode code, std::uint32_t val);
		// jump format with 56bit parameter
		void jFormat(InstCode code, const std::string & destination);
		// sysCall Format with 8, 16 and 32 bit parameter
		void sFormat(InstCode code, std::uint8_t args8, std::uint16_t arg16, std::uint32_t args32);
		
		void dFormat(InstCode code, std::uint64_t arg56);
	
		PseudoAssembler pseudoAssembler;
		std::map<std::string, std::uint64_t> markers;
	};
}