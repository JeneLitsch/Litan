#pragma once
#include <string>
#include <vector>
#include "LtnaTokenPackage.hxx"

namespace ltna {
	class AssemblerParser {
	public:
		std::vector<TokenPackage> parse(const std::string & code) const;
	private:
		void parseLine(const std::string line, std::uint64_t lineNr, std::vector<TokenPackage> & tokenPackages) const;
		std::vector<std::string> split(const std::string & str, char delim) const;
	};
}