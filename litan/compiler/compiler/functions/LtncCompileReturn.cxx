#include "LtncCompilerFunctions.hxx"

ltn::c::StmtInfo ltn::c::compile::returnStatement(CompilerPack & compPkg, const StmtReturn & stmt) {
	CodeBuffer code = compPkg.codeBuffer();
	FunctionSignature signature = compPkg.getSymbolTable().currentFxSignature();
	if(stmt.expr) {
		ExprInfo exprInfo = expression(compPkg, *stmt.expr);
		if(exprInfo.typeId != signature.returnType) {
			throw error::unmatchingReturnType(signature.returnType, exprInfo.typeId, stmt.debugInfo);
		}
		code << exprInfo.code; 
	}
	else {
		if(TypeId(TVoid) != signature.returnType) {
			throw error::unmatchingReturnType( signature.returnType, TVoid, stmt.debugInfo);
		}
	}
	code << AssemblyCode("return");
	return StmtInfo(code, 0);
}
