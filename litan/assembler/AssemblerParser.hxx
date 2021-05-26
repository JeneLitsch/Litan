#pragma once
#include <string>
#include <vector>
#include "TokenPackage.hxx"

namespace ltn{
	class AssemblerParser {
	public:
		std::vector<TokenPackage> parse(const std::string & code) const;
	private:
		void parseLine(const std::string line, std::vector<TokenPackage> & tokenPackages) const;
		std::vector<std::string> split(const std::string & str, char delim) const;
	};
}