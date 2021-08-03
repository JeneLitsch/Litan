#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include "LtncFunctionSignature.hxx"

namespace ltnc {
	class TokenDebugInfo {
	public:
		TokenDebugInfo(
			unsigned lineNr,
			unsigned column,
			const std::string & lexeme);
		
		TokenDebugInfo();

		unsigned lineNr;
		unsigned column;
		std::string lexeme;
	};
}