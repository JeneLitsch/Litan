#include "LtncNodeDebugInfo.hxx"

ltnc::NodeDebugInfo::NodeDebugInfo(
	const TokenDebugInfo & tokenInfo,
	const FunctionSignature & inFunction)
:	tokenInfo(tokenInfo),
	inFunction(inFunction) {}

