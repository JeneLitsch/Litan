#pragma once
#include <map>
#include "MinorScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class IifeScope final : public MinorScope {
	public:
		IifeScope(const Scope * outer);
	};
}