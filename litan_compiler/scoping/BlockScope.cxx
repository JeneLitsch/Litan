#include "BlockScope.hxx"
#include "litan_compiler/CompilerError.hxx"

namespace ltn::c {
	BlockScope::BlockScope(const Scope * outer) : MinorScope { outer } {}
}