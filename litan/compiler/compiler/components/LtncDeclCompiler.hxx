#pragma once
#include <string>
#include "LtncStmtInfo.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncDecl.hxx"
#include "LtncStmt.hxx"
#include "LtncAst.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncStmtCompiler.hxx"
namespace ltnc {
	class DeclCompiler {
	public:
		DeclCompiler(StmtCompiler & stmtCompiler);
		StmtInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<DeclFunction> & decl) const;
	private:
		std::string fxComment(
			const std::shared_ptr<DeclFunction> & decl) const;
		StmtCompiler & stmtCompiler;
	};
}