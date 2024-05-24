#pragma once
#include "MinorScope.hxx"

namespace ltn::c {
	class ExceptScope : public MinorScope {
	public:
		ExceptScope(const Scope & scope);
	};
}