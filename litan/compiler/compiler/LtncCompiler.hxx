#pragma once
#include "LtncStmtCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncDeclCompiler.hxx"
namespace ltnc {
	class Compiler {

	public:
		Compiler() : declCompiler(stmtCompiler), stmtCompiler(exprCompiler, asmbCompiler) {}
		std::string compile(
			std::shared_ptr<Program> program,
			const CompilerSettings & settings);
	private:
		DeclCompiler declCompiler;
		StmtCompiler stmtCompiler;
		ExprCompiler exprCompiler;
		AsmbCompiler asmbCompiler;
	};
}