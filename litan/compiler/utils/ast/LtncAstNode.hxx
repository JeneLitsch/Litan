#pragma once
#include "LtncDebugInfo.hxx"
namespace ltn::c {
	struct AstNode {
		AstNode(const DebugInfo & debugInfo) 
			: debugInfo(debugInfo) {}
		DebugInfo debugInfo;
	};
}