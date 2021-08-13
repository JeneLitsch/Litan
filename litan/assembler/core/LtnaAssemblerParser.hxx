#pragma once
#include <string>
#include <vector>
#include "LtnaTokenPackage.hxx"

namespace ltn::a {
	class AssemblerParser {
	public:
		std::vector<TokenPackage> parse(const std::string & code) const;
	};
}