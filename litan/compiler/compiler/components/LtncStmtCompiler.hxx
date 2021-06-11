#pragma once
#include <string>
#include <map>
#include <stack>
#include <cstdint>

#include "LtncStmtInfo.hxx"

#include "LtncAst.hxx"
#include "LtncType.hxx"
#include "LtncScope.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncScopeStack.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncAsmbCompiler.hxx"

namespace ltnc {
	class StmtCompiler : public CompilerComponent<StmtInfo, Stmt> {
	public:
		StmtCompiler(ExprCompiler & exprCompiler, AsmbCompiler & asmbCompiler) 
			: exprCompiler(exprCompiler), asmbCompiler(asmbCompiler) {}

		StmtInfo compile(CompilerPack & compPkg, const std::shared_ptr<Stmt> & stmt) const;

		StmtInfo compileStmt(CompilerPack & compPkg, std::shared_ptr<Stmt> stmt) const;
		StmtInfo compileIf(CompilerPack & compPkg, std::shared_ptr<StmtIf> stmt) const;
		StmtInfo compileAssign(CompilerPack & compPkg, std::shared_ptr<StmtAssign> stmt) const;
		StmtInfo compileBlock(CompilerPack & compPkg, std::shared_ptr<StmtBlock> stmt) const;
		StmtInfo compileFor(CompilerPack & compPkg, std::shared_ptr<StmtFor> stmt) const;
		StmtInfo compileRepeat(CompilerPack & compPkg, std::shared_ptr<StmtRepeat> stmt) const;
		StmtInfo compileWhile(CompilerPack & compPkg, std::shared_ptr<StmtWhile> stmt) const;
		StmtInfo compileEval(CompilerPack & compPkg, std::shared_ptr<StmtExpr> stmt) const;
		StmtInfo compileReturn(CompilerPack & compPkg, std::shared_ptr<StmtReturn> stmt) const;

		ExprCompiler & exprCompiler;
		AsmbCompiler & asmbCompiler;
	};
}