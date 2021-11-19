#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Declaration : public Node {
		Declaration(const lex::DebugInfo & debugInfo) : Node(debugInfo) {}
		virtual ~Declaration() = default;
	};
}