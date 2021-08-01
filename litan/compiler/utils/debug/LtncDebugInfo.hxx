#pragma once
#include <cstdint>
#include <string>
namespace ltnc {
	class DebugInfo {
	public:
		DebugInfo(
			unsigned lineNr,
			unsigned column,
			const std::string & lexeme);
		unsigned lineNr;
		unsigned column;
		std::string lexeme;
	};
}