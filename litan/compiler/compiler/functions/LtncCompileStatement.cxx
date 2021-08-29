#include "LtncCompilerFunctions.hxx"

ltn::c::StmtInfo ltn::c::compile::statement(CompilerPack & compPkg, const Stmt & stmt) {
	if(auto stmt_ = dynamic_cast<const StmtAssign*>(&stmt)) {
		return assign(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtBlock*>(&stmt)) {
		return codeBlock(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtIf*>(&stmt)) {
		return ifElse(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtFor*>(&stmt)) {
		return forLoop(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtRepeat*>(&stmt)) {
		return repeatLoop(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtWhile*>(&stmt)) {
		return whileLoop(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtExpr*>(&stmt)) {
		return justAnExpression(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtReturn*>(&stmt)) {
		return returnStatement(compPkg, *stmt_);
	}
	if(auto stmt_ = dynamic_cast<const StmtAsm*>(&stmt)) {
		return StmtInfo(assembly(compPkg, *stmt_), 0);
	}
	throw error::invalidStatement(stmt.debugInfo);
}

ltn::c::StmtInfo ltn::c::compile::justAnExpression(CompilerPack & compPkg, const StmtExpr & stmt) {
	ExprInfo exprInfo = expression(compPkg, *stmt.expr);
	CodeBuffer code = compPkg.codeBuffer();
	code << exprInfo.code;
	if(exprInfo.typeId != TypeId(TVoid)) {
		code << AssemblyCode("scrap");
	}
	return StmtInfo(code, 0);
}

