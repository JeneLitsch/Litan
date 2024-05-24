#pragma once
#include <map>
#include "MajorScope.hxx"
#include "NamespaceScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class FunctionScope final : public MajorScope {
	public:
		FunctionScope(const NamespaceScope & namspace_scope, Qualifiers qualifiers);
	private:
	};
}