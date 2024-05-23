#include "FunctionScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	FunctionScope::FunctionScope(
		const Namespace & namespaze,
		Qualifiers qualifiers,
		const GlobalScope & global_scope) 
		: MajorScope { namespaze, qualifiers, global_scope.get_context()} {}
}