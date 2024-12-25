#pragma once
#include <map>
#include "MajorScope.hxx"

namespace ltn::c {
	// Major Scope for e.g. functions 
	class CaseScope final : public MajorScope {
	public:
		CaseScope(const Scope * outer);
	private:
		InvalidFunctionTable fx_table {"case"};
		InvalidGlobalTable global_table {"case"};
		Context context;
	};
}