#include "BlockScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	BlockScope::BlockScope(const Scope * outer) : MinorScope { outer } {}
}