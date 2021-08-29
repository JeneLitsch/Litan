#include "LtncCompilerFunctions.hxx"

ltn::c::CodeBuffer ltn::c::compile::assembly(CompilerPack & compPkg, const StmtAsm & stmtAsm) {
	CodeBuffer code = compPkg.codeBuffer();
	code << AssemblyCode(stmtAsm.instructions);
	return code;
}