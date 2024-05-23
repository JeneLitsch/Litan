#include "ExceptScope.hxx"

namespace ltn::c {
	ExceptScope::ExceptScope(const Scope & scope)
		: MajorScope { scope.get_namespace(), Qualifiers::none, scope.get_context() } {}
}