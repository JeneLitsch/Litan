#pragma once
#include <string>
#include <map>
#include <stack>
#include <cstdint>
#include "LtncAst.hxx"
#include "LtncType.hxx"
#include "LtncScope.hxx"
#include "LtncBaseCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncScopeStack.hxx"
#include "LtncCompilerPack.hxx"

namespace ltnc {
	class StmtCompiler : public BaseCompiler {
	public:
		StmtCompiler(ExprCompiler & exprCompiler) : exprCompiler(exprCompiler) {}
		std::string compileProgram(CompilerPack & compPkg, std::shared_ptr<Program> program);
	private:
		std::string compileStmt(CompilerPack & compPkg, std::shared_ptr<Stmt> stmt);
		std::string compilePrint(CompilerPack & compPkg, std::shared_ptr<StmtPrint> stmt);
		std::string compileIf(CompilerPack & compPkg, std::shared_ptr<StmtIf> stmt);
		std::string compileAssign(CompilerPack & compPkg, std::shared_ptr<StmtAssign> stmt);
		std::string compileBlock(CompilerPack & compPkg, std::shared_ptr<StmtBlock> stmt);
		std::string compileFor(CompilerPack & compPkg, std::shared_ptr<StmtFor> stmt);
		std::string compileRepeat(CompilerPack & compPkg, std::shared_ptr<StmtRepeat> stmt);
		std::string compileWhile(CompilerPack & compPkg, std::shared_ptr<StmtWhile> stmt);
		std::string compileFunction(CompilerPack & compPkg, std::shared_ptr<DeclFunction> stmt);
		std::string compileEval(CompilerPack & compPkg, std::shared_ptr<StmtExpr> stmt);
		std::string compileReturn(CompilerPack & compPkg, std::shared_ptr<StmtReturn> stmt);

		ExprCompiler & exprCompiler;
	};
}