#pragma once
#include "LtncFunction.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncCompilerPack.hxx"
namespace ltn::c {
	class CtorGenerator {
	public:
		CodeBuffer defaultCtor(
			CompilerPack & compilePkg,
			const Type & type) const;

		CodeBuffer parameterCtor(
			CompilerPack & compilePkg,
			const Type & type) const;
	};
}