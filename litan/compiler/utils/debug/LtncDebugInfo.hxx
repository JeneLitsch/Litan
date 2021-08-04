#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include "LtncFunctionSignature.hxx"

namespace ltnc {
	class DebugInfo {
	public:
		DebugInfo(
			unsigned lineNr,
			unsigned column,
			const std::string & lexeme);
		
		DebugInfo();

		unsigned lineNr;
		unsigned column;
		std::string lexeme;

		std::optional<FunctionSignature> inFunction;
	};
}