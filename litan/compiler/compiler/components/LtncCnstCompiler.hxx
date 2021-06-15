#pragma once
#include <string>
#include "LtncAst.hxx"
#include "LtncExprInfo.hxx"
#include "LtncCodeBuffer.hxx"
#include "LtncCompilerPack.hxx"

namespace ltnc {
	class ExprCompiler;
	class CnstCompiler {
	public:
		CnstCompiler(const ExprCompiler & exprCompiler);
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;

	private:
		ExprInfo defaultConstructor(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;

		ExprInfo parameterConstructor(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;
		
		const ExprCompiler & exprCompiler;		
	};
}