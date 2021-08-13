#include "LtncCompilerFunctions.hxx"

ltn::c::StmtInfo ltn::c::compile::assign(CompilerPack & compPkg, const StmtAssign & stmt) {
	auto expr = expression(compPkg, *stmt.expr);
	auto access = var(compPkg, *stmt.var, expr);
	const SymbolTable & sTable = compPkg.getSymbolTable();
	const Type & typeL = sTable.match(stmt.debugInfo, expr.typeId);
	
	bool castable = typeL.isCastableTo(access.typeId);
	if(!castable) {
		throw error::incompatibleTypes(stmt.debugInfo, expr.typeId, access.typeId);
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << access.code;
	return StmtInfo(code, 0);
}
