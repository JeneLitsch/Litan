#pragma once
#include <string>
#include "LtncCompilerComponent.hxx"
#include "LtncAst.hxx"
#include "LtncExprInfo.hxx"
namespace ltnc {
	class ExprCompiler;
	class VariCompiler;
	class DstrCompiler  {
	public:
		DstrCompiler(
			const ExprCompiler & exprCompiler,
			const VariCompiler & variCompiler);
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprDel> & exprNew) const;
		
	private:
		const ExprCompiler & exprCompiler;
		const VariCompiler & variCompiler;
	};
}