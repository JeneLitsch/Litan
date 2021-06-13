#pragma once
#include "LtncStmtCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncDeclCompiler.hxx"
#include "LtncCnstCompiler.hxx"
#include "LtncDstrCompiler.hxx"
#include "LtncVariCompiler.hxx"
namespace ltnc {
	class Compiler {

	public:
		
		Compiler() : 
			declCompiler(stmtCompiler),
			stmtCompiler(exprCompiler, asmbCompiler, variCompiler),
			exprCompiler(cnstCompiler, dstrCompiler, variCompiler),
			dstrCompiler(exprCompiler, variCompiler)
			{}
		
		std::string compile(
			std::shared_ptr<Program> program,
			const CompilerSettings & settings);
	private:
		DeclCompiler declCompiler;
		StmtCompiler stmtCompiler;
		ExprCompiler exprCompiler;
		AsmbCompiler asmbCompiler;
		CnstCompiler cnstCompiler;
		DstrCompiler dstrCompiler;
		VariCompiler variCompiler;
	};
}