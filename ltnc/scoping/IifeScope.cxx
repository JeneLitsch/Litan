#include "IifeScope.hxx"
#include "ltnc/CompilerError.hxx"

namespace ltn::c {
	IifeScope::IifeScope(const Scope * outer) : MinorScope { outer } {}
}