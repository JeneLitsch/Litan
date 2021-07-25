#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::assign(CompilerPack & compPkg, const StmtAssign & stmt) {
	auto expr = expression(compPkg, *stmt.expr);
	auto access = var(compPkg, *stmt.var, expr);
	if(expr.typeId != access.typeId) {
		throw std::runtime_error("Types in Assignment do not match: " 
			+ access.typeId.ns.str() + access.typeId.name + "=" + expr.typeId.ns.str() + expr.typeId.name);
	}
	CodeBuffer code = compPkg.codeBuffer();
	code << access.code;
	return StmtInfo(code, 0);
}
