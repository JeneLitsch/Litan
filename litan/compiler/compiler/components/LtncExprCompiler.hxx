#pragma once
#include <memory>
#include "LtncType.hxx"
#include "LtncExpr.hxx"
#include "LtncScope.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncCompilerComponent.hxx"
#include "LtncExprInfo.hxx"
#include "LtncEvaluator.hxx"
namespace ltnc {
	class ExprCompiler : public CompilerComponent<ExprInfo, Expr> {
	public:

		
		virtual ExprInfo compile(CompilerPack & compPkg, const std::shared_ptr<Expr> & expr) const override;
		ExprInfo compileExpr(CompilerPack & compPkg, std::shared_ptr<Expr> expr) const;

		ExprInfo compileBinary(CompilerPack & compPkg, std::shared_ptr<ExprBinary> expr) const;
		
		// optimzed binary operator
		ExprInfo buildBinary(
			CompilerPack & compPkg,
			std::shared_ptr<ExprBinary> expr,
			const std::string & command,
			const Evaluator & eval) const;

		// unoptimized binary operator
		ExprInfo buildBinary(
			CompilerPack & compPkg,
			std::shared_ptr<ExprBinary> expr,
			const std::string & command) const;

		ExprInfo compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr) const;
		ExprInfo compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr) const;
		ExprInfo compileStrLit(CompilerPack & compPkg, std::shared_ptr<ExprStrLiteral> expr) const;
		ExprInfo compileVar(CompilerPack & compPkg, std::shared_ptr<ExprVar> expr) const;

		ExprInfo compileCall(CompilerPack & compPkg, std::shared_ptr<ExprCall> expr) const;

	private:
		std::string getSuffux(const ExprInfo & l, const ExprInfo & r) const;

	};
}