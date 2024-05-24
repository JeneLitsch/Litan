#include "ExceptScope.hxx"

namespace ltn::c {
	ExceptScope::ExceptScope(const Scope & scope)
		: MinorScope { &scope } {}
}