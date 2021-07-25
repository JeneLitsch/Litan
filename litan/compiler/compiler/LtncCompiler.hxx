#pragma once
#include <map>
#include "LtncStmtCompiler.hxx"
#include "LtncExprCompiler.hxx"
#include "LtncDeclCompiler.hxx"
#include "LtncVariCompiler.hxx"

#include "LtncConstructorGenerator.hxx"

namespace ltnc {
	class Compiler {

	public:
		
		Compiler() : 
			declCompiler(stmtCompiler),
			stmtCompiler(exprCompiler, asmbCompiler, variCompiler),
			exprCompiler(variCompiler) {}
		
		std::string compile(
			std::shared_ptr<Program> program,
			const CompilerSettings & settings);
	private:
		DeclCompiler declCompiler;
		StmtCompiler stmtCompiler;
		ExprCompiler exprCompiler;
		AsmbCompiler asmbCompiler;
		VariCompiler variCompiler;

		ConstructorGenerator constructorGenerator;
	};
}