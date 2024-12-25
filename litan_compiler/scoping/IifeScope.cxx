#include "IifeScope.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	IifeScope::IifeScope(const Scope * outer) : MinorScope { outer } {}
}