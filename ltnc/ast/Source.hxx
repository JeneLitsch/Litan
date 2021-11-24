#pragma once
#include "Node.hxx"
#include "Function.hxx"

namespace ltn::c::ast {
	struct Source : public Node {
		Source(
			std::vector<std::unique_ptr<Functional>> && functions,
			const lex::DebugInfo & debugInfo)
			:	Node(debugInfo),
				functions(std::move(functions)) {}
		virtual ~Source() = default;
		const std::vector<std::unique_ptr<Functional>> functions;
	};
}