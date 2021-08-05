#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::codeBlock(CompilerPack & compPkg, const StmtBlock & block) {
	compPkg.getSymbolTable().addBlockScope();
	CodeBuffer code = compPkg.codeBuffer();

	unsigned stackalloc = 0;
	unsigned varCount = 0;
	
	for(const auto & stmt : block.statements) {
		if(auto var = std::dynamic_pointer_cast<StmtVar>(stmt)) {
			compPkg.getSymbolTable().match(var->typeId);
			compPkg.getSymbolTable().insert(var->varId, var->typeId);
			varCount++;
			if(var->typeId == TVoid) {
				throw error::voidVariable(var->debugInfo, var->varId);
			}
		}
		else {
			StmtInfo stmtInfo = statement(compPkg, *stmt);
			stackalloc = std::max<unsigned>(stackalloc, stmtInfo.stackalloc);
			code << stmtInfo.code;
		}
	}

	stackalloc += varCount;
	compPkg.getSymbolTable().remove();
	return StmtInfo(code, stackalloc);
}