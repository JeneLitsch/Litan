#include "FunctionScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	FunctionScope::FunctionScope(
		const Namespace & namespaze,
		bool c0nst,
		stx::reference<Context> context) 
		: MajorScope { namespaze, c0nst, context} {}
}