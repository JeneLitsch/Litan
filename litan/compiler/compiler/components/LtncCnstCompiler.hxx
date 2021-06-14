#pragma once
#include <string>
#include "LtncAst.hxx"
#include "LtncExprInfo.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncCompilerPack.hxx"

namespace ltnc {
	class CnstCompiler {
	public:
		CnstCompiler();
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;

	private:
		ExprInfo defaultConstructor(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;	
	};
}