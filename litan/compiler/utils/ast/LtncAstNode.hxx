#pragma once
#include "LtncDebugInfo.hxx"
namespace ltnc {
	struct AstNode {
		AstNode(const DebugInfo & debugInfo) 
			: debugInfo(debugInfo) {}
		DebugInfo debugInfo;
	};
}