#include "FunctionScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {

	FunctionScope::FunctionScope(
		const ast::Namespace & namespaze,
		bool c0nst) 
	: MajorScope { namespaze, c0nst} {}
}