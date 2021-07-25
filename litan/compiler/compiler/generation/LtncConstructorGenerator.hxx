#pragma once
#include "LtncFunction.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncCompilerPack.hxx"
namespace ltnc {
	struct Constructor {
		CodeBuffer code;
	};
	class ConstructorGenerator {
	public:
		CodeBuffer defaultCtor(
			CompilerPack & compilePkg,
			const Type & type) const;

		CodeBuffer parameterCtor(
			CompilerPack & compilePkg,
			const Type & type) const;
	};
}