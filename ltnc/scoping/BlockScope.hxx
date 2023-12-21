#pragma once
#include <map>
#include "MinorScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class BlockScope final : public MinorScope {
	public:
		BlockScope(const Scope * outer);
	};
}