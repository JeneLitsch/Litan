#pragma once
#include <memory>
#include "LtncType.hxx"
#include "LtncExpr.hxx"
#include "LtncScope.hxx"
#include "LtncBaseCompiler.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncExprInfo.hxx"
#include "LtncEvaluator.hxx"
namespace ltnc {
	class ExprCompiler : public BaseCompiler {
	public:

		
		ExprInfo compileExpr(CompilerPack & compPkg, std::shared_ptr<Expr> expr);

		ExprInfo compileBinary(CompilerPack & compPkg, std::shared_ptr<ExprBinary> expr);
		
		// optimzed binary operator
		ExprInfo buildBinary(
			CompilerPack & compPkg,
			std::shared_ptr<ExprBinary> expr,
			const std::string & command,
			const Evaluator & eval);

		// unoptimized binary operator
		ExprInfo buildBinary(
			CompilerPack & compPkg,
			std::shared_ptr<ExprBinary> expr,
			const std::string & command);

		ExprInfo compileIntLit(CompilerPack & compPkg, std::shared_ptr<ExprIntLiteral> expr);
		ExprInfo compileFltLit(CompilerPack & compPkg, std::shared_ptr<ExprFltLiteral> expr);
		ExprInfo compileVar(CompilerPack & compPkg, std::shared_ptr<ExprVar> expr);

		ExprInfo compileCall(CompilerPack & compPkg, std::shared_ptr<ExprCall> expr);

	private:
		std::string getSuffux(const ExprInfo & l, const ExprInfo & r);

	};
}