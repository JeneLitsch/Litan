#pragma once
#include "LtncFunctionSignature.hxx"
#include "LtncTokenDebugInfo.hxx"
namespace ltnc {
	class NodeDebugInfo {
	public:
		NodeDebugInfo(
			const TokenDebugInfo & tokenInfo,
			const FunctionSignature & inFunction);

		TokenDebugInfo tokenInfo;
		FunctionSignature inFunction;
	};
}