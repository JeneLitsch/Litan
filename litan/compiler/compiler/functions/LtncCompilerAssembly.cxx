#include "LtncCompilerFunctions.hxx"

ltnc::CodeBuffer ltnc::compile::assembly(CompilerPack & compPkg, const StmtAsm & stmtAsm) {
	UNUSED(compPkg);
	CodeBuffer code = compPkg.codeBuffer();
	code << AssemblyCode(stmtAsm.instructions);
	return code;
}