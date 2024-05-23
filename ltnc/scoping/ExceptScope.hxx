#pragma once
#include "MajorScope.hxx"

namespace ltn::c {
	class ExceptScope : public MajorScope {
	public:
		ExceptScope(const Scope & scope);
	};
}