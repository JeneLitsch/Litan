#pragma once
#include <map>
#include "MajorScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class FunctionScope final : public MajorScope {
	public:
		FunctionScope(const Namespace & namespaze, bool c0nst);
	private:
	};
}