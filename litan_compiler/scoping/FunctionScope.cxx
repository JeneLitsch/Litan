#include "FunctionScope.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {

	FunctionScope::FunctionScope(
		const Namespace & namespaze,
		Qualifiers qualifiers,
		stx::reference<Context> context) 
		: MajorScope { namespaze, qualifiers, context} {}
}