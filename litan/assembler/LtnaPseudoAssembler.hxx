#pragma once
#include "LtnaTokenPackage.hxx"
#include <map>
#include "LtnExtSlot.hxx"
#include <set>
namespace ltna {
	// preprocessor for translate pseudo instructions, macros and preprocessor directives
	class PseudoAssembler {
	public:
		std::vector<TokenPackage> process(const std::vector<TokenPackage> & tokensPackages);

		void registerAlias(const std::string & alias, ltn::Slot slot, std::uint8_t funct);
	private:
		std::map<std::string, std::pair<ltn::Slot, std::uint8_t>> aliases;
		void processPkg(const TokenPackage & pkg);
		std::vector<TokenPackage> newPkgs;
	};
}