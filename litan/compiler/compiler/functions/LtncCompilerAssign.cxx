#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::assign(CompilerPack & compPkg, const StmtAssign & stmt) {
	auto expr = expression(compPkg, *stmt.expr);
	auto access = var(compPkg, *stmt.var, expr);
	const SymbolTable & sTable = compPkg.getSymbolTable();
	const Type & typeL = sTable.match(expr.typeId);
	
	bool castable = typeL.isCastableTo(access.typeId);
	if(!castable) {
		throw error::incompatibleTypes(stmt.debugInfo, expr.typeId, access.typeId);
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << access.code;
	return StmtInfo(code, 0);
}
