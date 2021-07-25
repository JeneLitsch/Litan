#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::returnStatement(CompilerPack & compPkg, const StmtReturn & stmt) {
	CodeBuffer code = compPkg.codeBuffer();
	FunctionSignature signature = compPkg.getSymbolTable().currentFxSignature();
	if(stmt.expr) {
		ExprInfo exprInfo = expression(compPkg, *stmt.expr);
		if(exprInfo.typeId != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
		code << exprInfo.code; 
	}
	else {
		if(TypeId(TVoid) != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
	}
	code << AssemblyCode("return");
	return StmtInfo(code, 0);
}
