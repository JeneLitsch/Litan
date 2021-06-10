#include "LtncAsmBlockCompiler.hxx"
#include "Unused.hxx"
std::string ltnc::AsmBlockCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<StmtAsm> & stmt) const {
	UNUSED(compPkg);
	std::string code;
	for(const std::string & instruction : stmt->instructions) {
		code += instruction + "\n";
	}
	return code;
}
