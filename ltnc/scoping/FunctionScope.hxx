#pragma once
#include <map>
#include "MajorScope.hxx"
#include "GlobalScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class FunctionScope final : public MajorScope {
	public:
		FunctionScope(const Namespace & namespaze, Qualifiers qualifiers, const GlobalScope & global_scope);
	private:
	};
}