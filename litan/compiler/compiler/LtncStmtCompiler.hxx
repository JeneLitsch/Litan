#pragma once
#include <string>
#include <map>
#include <stack>
#include <cstdint>

#include "LtncStmtInfo.hxx"

#include "LtncAst.hxx"
#include "LtncType.hxx"
#include "LtncScope.hxx"
#include "LtncBaseCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncScopeStack.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncAsmBlockCompiler.hxx"

namespace ltnc {
	class StmtCompiler : public BaseCompiler {
	public:
		StmtCompiler(ExprCompiler & exprCompiler) : exprCompiler(exprCompiler) {}
		std::string compileProgram(CompilerPack & compPkg, std::shared_ptr<Program> program);
	private:
		StmtInfo compileStmt(CompilerPack & compPkg, std::shared_ptr<Stmt> stmt);
		StmtInfo compileIf(CompilerPack & compPkg, std::shared_ptr<StmtIf> stmt);
		StmtInfo compileAssign(CompilerPack & compPkg, std::shared_ptr<StmtAssign> stmt);
		StmtInfo compileBlock(CompilerPack & compPkg, std::shared_ptr<StmtBlock> stmt);
		StmtInfo compileFor(CompilerPack & compPkg, std::shared_ptr<StmtFor> stmt);
		StmtInfo compileRepeat(CompilerPack & compPkg, std::shared_ptr<StmtRepeat> stmt);
		StmtInfo compileWhile(CompilerPack & compPkg, std::shared_ptr<StmtWhile> stmt);
		StmtInfo compileFunction(CompilerPack & compPkg, std::shared_ptr<DeclFunction> stmt);
		StmtInfo compileEval(CompilerPack & compPkg, std::shared_ptr<StmtExpr> stmt);
		StmtInfo compileReturn(CompilerPack & compPkg, std::shared_ptr<StmtReturn> stmt);

		ExprCompiler & exprCompiler;
		AsmBlockCompiler asmBlock;
	};
}