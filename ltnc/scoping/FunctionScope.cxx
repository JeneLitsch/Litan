#include "FunctionScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	FunctionScope::FunctionScope(
		const NamespaceScope & namspace_scope,
		Qualifiers qualifiers)
		: MajorScope { namspace_scope.get_namespace(), qualifiers, namspace_scope.get_context()} {}
}