#pragma once
#include "LtncNodeDebugInfo.hxx"
namespace ltnc {
	struct AstNode {
		AstNode() = default;
		AstNode(const NodeDebugInfo & debugInfo) 
			: debugInfo(debugInfo) {}
		std::optional<NodeDebugInfo> debugInfo;
	};
}