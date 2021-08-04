#pragma once
#include "Unused.hxx"

#include "LtncAst.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncCodeBuffer.hxx"

#include "LtncStmtInfo.hxx"
#include "LtncExprInfo.hxx"
#include "LtncError.hxx"
#include "LtncErrorCreationCompiler.hxx"

namespace ltnc {
	namespace compile {
		// Assembly Blocks
		
		CodeBuffer assembly(CompilerPack & compPkg, const StmtAsm & stmtAsm);


		// Declarations

		StmtInfo function(CompilerPack & compPkg, const DeclFunction & declFunction);
		

		// Statements

		StmtInfo statement(CompilerPack & compPkg, const Stmt & stmt);
		StmtInfo ifElse(CompilerPack & compPkg, const StmtIf & stmt);
		StmtInfo assign(CompilerPack & compPkg, const StmtAssign & stmt);
		StmtInfo codeBlock(CompilerPack & compPkg, const StmtBlock & stmt);
		StmtInfo forLoop(CompilerPack & compPkg, const StmtFor & stmt);
		StmtInfo repeatLoop(CompilerPack & compPkg, const StmtRepeat & stmt);
		StmtInfo whileLoop(CompilerPack & compPkg, const StmtWhile & stmt);
		StmtInfo justAnExpression(CompilerPack & compPkg, const StmtExpr & stmt);
		StmtInfo returnStatement(CompilerPack & compPkg, const StmtReturn & stmt);



		// Expressions

		ExprInfo expression(CompilerPack & compPkg, const Expr & expr);		
		ExprInfo binaryExpr(CompilerPack & compPkg, const ExprBinary & expr);
		ExprInfo unary(CompilerPack & compPkg, const ExprUnary & expr);
		ExprInfo intLiteral(CompilerPack & compPkg, const ExprIntLiteral & expr);
		ExprInfo floatLiteral(CompilerPack & compPkg, const ExprFltLiteral & expr);
		ExprInfo stringLiteral(CompilerPack & compPkg, const ExprStrLiteral & expr);		
		ExprInfo call(CompilerPack & compPkg, const ExprCall & expr);
		ExprInfo var(CompilerPack & compPkg, const ExprVar & var, const std::optional<ExprInfo> & expr);
		ExprInfo nul();
	}
}