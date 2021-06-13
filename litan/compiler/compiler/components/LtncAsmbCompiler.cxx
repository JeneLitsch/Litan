#include "LtncAsmbCompiler.hxx"
#include "Unused.hxx"
ltnc::CodeBuffer ltnc::AsmbCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<StmtAsm> & stmt) const {
	UNUSED(compPkg);
	CodeBuffer code = compPkg.codeBuffer();
	code << AssemblyCode(stmt->instructions);
	return code;
}
