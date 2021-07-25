#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::codeBlock(CompilerPack & compPkg, const StmtBlock & block) {
	compPkg.getSymbolTable().addBlockScope();
	CodeBuffer code = compPkg.codeBuffer();
	for(const auto & decl : block.declarations) {
		compPkg.getSymbolTable().match(decl->typeId);
		compPkg.getSymbolTable().insert(decl->name, decl->typeId);
		Var counter = compPkg.getSymbolTable().match(VarId(decl->name));
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