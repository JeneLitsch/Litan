#pragma once
#include <memory>
#include "ltnc/lex/DebugInfo.hxx"
namespace ltn::c::ast {
	struct Node {
		Node(const lex::DebugInfo & debugInfo)
			:	debugInfo(debugInfo) {}
		virtual ~Node() = default;
		const lex::DebugInfo debugInfo;
	};
}