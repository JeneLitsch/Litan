#pragma once
#include "Node.hxx"
#include "Function.hxx"

namespace ltn::c::ast {
	struct Source {
		virtual ~Source() = default;
		std::vector<std::unique_ptr<Function>> functions;
	};
}