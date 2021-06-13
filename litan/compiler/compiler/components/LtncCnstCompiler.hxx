#pragma once
#include <string>
#include "LtncCompilerComponent.hxx"
#include "LtncAst.hxx"
#include "LtncExprInfo.hxx"
namespace ltnc {
	class CnstCompiler : public CompilerComponent<ExprInfo, ExprNew> {
	public:
		CnstCompiler();
		virtual ExprInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const override;

	private:
		ExprInfo defaultConstructor(
			CompilerPack & compPkg,
			const std::shared_ptr<ExprNew> & exprNew) const;	
	};
}