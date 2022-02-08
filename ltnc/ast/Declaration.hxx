#pragma once
#include "Node.hxx"

namespace ltn::c::ast {
	struct Declaration : public Node {
		Declaration(const SourceLocation & location) : Node(location) {}
		virtual ~Declaration() = default;
	};
}