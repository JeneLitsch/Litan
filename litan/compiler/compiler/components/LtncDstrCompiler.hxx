#pragma once
#include <string>
#include "LtncAst.hxx"
#include "LtncExprInfo.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncCodeBuffer.hxx"
namespace ltnc {
	class ExprCompiler;
	class VariCompiler;
	class DstrCompiler  {
	public:
		DstrCompiler(
			const VariCompiler & variCompiler);
		ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprDel> & exprNew) const;
		
	private:
		ExprInfo nullPtr(const Type & type) const;
		const VariCompiler & variCompiler;
	};
}