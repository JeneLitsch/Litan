#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::repeatLoop(CompilerPack & compPkg, const StmtRepeat & stmt) {
	
	CodeBuffer code = compPkg.codeBuffer();
	// From and to expression
	ExprInfo expr = expression(compPkg, *stmt.expr); 


	if(expr.typeId != TypeId(TInt)){
		throw error::repeatCountNotInt(stmt.debugInfo);
	}
	
	compPkg.getSymbolTable().addBlockScope();
	// iteration variable
	// create code inside loop
	StmtInfo codeStmt = statement(compPkg, *stmt.stmt);
	compPkg.getSymbolTable().remove();


	code << Inst::newi(0UL);
	code << expr.code;
	code << AssemblyCode("dec");
	code << AssemblyCode("loop::range");
	code << codeStmt.code;
	code << AssemblyCode("loop::cont");

	// create code
	return StmtInfo(code, codeStmt.stackalloc);
}


ltnc::StmtInfo ltnc::compile::forLoop(CompilerPack & compPkg, const StmtFor & stmt) {
	// From and to expression
	ExprInfo from = expression(compPkg, *stmt.exprFrom); 
	ExprInfo to = expression(compPkg, *stmt.exprTo);

	if(from.typeId != TInt) {
		throw error::lowerBoundNotInt(stmt.debugInfo);
	}

	if(to.typeId != TInt) {
		throw error::upperBoundNotInt(stmt.debugInfo);
	}

	compPkg.getSymbolTable().addBlockScope();
	// iteration variable
	compPkg.getSymbolTable().insert(stmt.name, TypeId(TInt));
	const Var & counter = compPkg.getSymbolTable().match(VarId(stmt.name));
	StmtInfo body = statement(compPkg, *stmt.stmt);

	compPkg.getSymbolTable().remove();

	CodeBuffer code = compPkg.codeBuffer();
	code << from.code;
	code << to.code;
	code << AssemblyCode("loop::range");
	code << AssemblyCode("loop::idx");
	code << Inst::store(counter.addr);
	code << body.code;
	code << AssemblyCode("loop::cont");

	return StmtInfo(code, body.stackalloc + 1);
}


ltnc::StmtInfo ltnc::compile::whileLoop(CompilerPack & compPkg, const StmtWhile & stmt) {
	auto codeExpr = expression(compPkg, *stmt.expr); 
	auto codeStmt = statement(compPkg, *stmt.stmt);
	auto endMark = compPkg.getSymbolTable().makeJumpMark("LOOP_END");
	auto loopMark = compPkg.getSymbolTable().makeJumpMark("LOOP");
	
	CodeBuffer code = compPkg.codeBuffer();
	code << AssemblyCode("-> " + loopMark);
	code << codeExpr.code;
	code << AssemblyCode("ifnot");
	code << AssemblyCode("goto " + endMark);
	code << codeStmt.code;
	code << AssemblyCode("goto " + loopMark);
	code << AssemblyCode("-> " + endMark);

	return StmtInfo(code, codeStmt.stackalloc);
}