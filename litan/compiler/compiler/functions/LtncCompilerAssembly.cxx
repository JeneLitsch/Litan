#include "LtncCompilerFunctions.hxx"

ltnc::CodeBuffer ltnc::compile::assembly(CompilerPack & compPkg, const StmtAsm & stmtAsm) {
	CodeBuffer code = compPkg.codeBuffer();
	code << AssemblyCode(stmtAsm.instructions);
	return code;
}