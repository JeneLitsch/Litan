#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::codeBlock(CompilerPack & compPkg, const StmtBlock & block) {
	compPkg.getSymbolTable().addBlockScope();
	CodeBuffer code = compPkg.codeBuffer();

	for(const auto & decl : block.declarations) {
		compPkg.getSymbolTable().match(decl->typeId);
		compPkg.getSymbolTable().insert(decl->varId, decl->typeId);
		if(decl->typeId == TVoid) {
			throw error::voidVariable(decl->debugInfo, decl->varId);
		}
	}

	unsigned stackalloc = 0;
	
	for(const auto & stmt : block.statements) {
		StmtInfo stmtInfo = statement(compPkg, *stmt);
		stackalloc = std::max<unsigned>(stackalloc, stmtInfo.stackalloc);
		code << stmtInfo.code;
	}

	stackalloc += block.declarations.size();
	compPkg.getSymbolTable().remove();
	return StmtInfo(code, stackalloc);
}