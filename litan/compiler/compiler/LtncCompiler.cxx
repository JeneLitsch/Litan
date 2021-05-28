#include "LtncCompiler.hxx"

std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	unsigned optimizations,
	bool comments){
	CompilerPack compPkg;
	this->exprCompiler.activateComments(comments);
	this->stmtCompiler.activateComments(comments);
	this->stmtCompiler.setOptimization(optimizations);
	this->exprCompiler.setOptimization(optimizations);
	return stmtCompiler.compileProgram(compPkg, program);
}
