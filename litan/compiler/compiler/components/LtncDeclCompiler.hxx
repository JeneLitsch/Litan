#pragma once
#include <string>
#include "LtncStmtInfo.hxx"
#include "LtncCompilerPack.hxx"
#include "LtncDecl.hxx"
#include "LtncStmt.hxx"
#include "LtncCompilerComponent.hxx"
#include "LtncAst.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncStmtCompiler.hxx"
namespace ltnc {
	class DeclCompiler : public CompilerComponent<StmtInfo, DeclFunction> {
	public:
		DeclCompiler(StmtCompiler & stmtCompiler);
		virtual StmtInfo compile(
			CompilerPack & compPkg,
			const std::shared_ptr<DeclFunction> & decl) const override;
	private:
		std::string fxComment(
			CompilerPack & compPkg,
			const std::shared_ptr<DeclFunction> & decl) const;
		StmtCompiler & stmtCompiler;
	};
}