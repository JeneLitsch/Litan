#pragma once
#include "TokenPackage.hxx"
#include <map>
#include "IExtension.hxx"
#include <set>
namespace ltn{
	// preprocessor for translate pseudo instructions, macros and preprocessor directives
	class PseudoAssembler {
	public:
		std::vector<TokenPackage> process(const std::vector<TokenPackage> & tokensPackages, const std::vector<std::string> & includeDirectories);

		void registerAlias(const std::string & alias, IExtension::Slot slot, std::uint8_t funct);
	private:
		std::map<std::string, std::pair<IExtension::Slot, std::uint8_t>> aliases;
		void includeFile(const std::string & path);

		void processPkg(const TokenPackage & pkg);

		std::set<std::string> includeGuard;
		std::vector<TokenPackage> newPkgs;
		std::vector<std::string> includeDirectories;
	};
}