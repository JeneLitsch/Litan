#include "LtncCompiler.hxx"

std::string ltnc::Compiler::compile(
	std::shared_ptr<Program> program,
	const CompilerSettings & settings){
	CompilerPack compPkg(settings);
	return stmtCompiler.compileProgram(compPkg, program);
}
