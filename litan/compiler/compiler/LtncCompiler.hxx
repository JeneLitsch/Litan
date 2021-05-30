#pragma once
#include "LtncStmtCompiler.hxx"
#include "LtncExprCompiler.hxx"
namespace ltnc {
	class Compiler : public BaseCompiler {

	public:
		Compiler() : stmtCompiler(exprCompiler) {}
		std::string compile(
			std::shared_ptr<Program> program,
			const CompilerSettings & settings);
	private:
		StmtCompiler stmtCompiler;
		ExprCompiler exprCompiler;
	};
}