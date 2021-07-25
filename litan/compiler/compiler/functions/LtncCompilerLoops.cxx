#include "LtncCompilerFunctions.hxx"

ltnc::StmtInfo ltnc::compile::repeatLoop(CompilerPack & compPkg, const StmtRepeat & stmt) {
	
	CodeBuffer code = compPkg.codeBuffer();
	// From and to expression
	ExprInfo expr = expression(compPkg, *stmt.expr); 


	if(expr.typeId != TypeId(TInt)){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}
	
	compPkg.getSymbolTable().addBlockScope();
	// iteration variable
	// create code inside loop
	StmtInfo codeStmt = codeBlock(compPkg, *stmt.stmt);
	compPkg.getSymbolTable().remove();

	// unroll repeat
	if(expr.constValue) {
		std::int64_t amount = std::get<std::int64_t>(expr.constValue->value);
		if(amount <= 0) {
			std::cout << ">> [Warning] repeat loop: needs to be bigger than 0" << std::endl;
		}

		bool shouldBeOptimized =
			(compPkg.getSettings().getOptimizationLevel() == 1 && amount < 64) ||
			(compPkg.getSettings().getOptimizationLevel() == 2 && amount < 128) ||
			(compPkg.getSettings().getOptimizationLevel() >= 3 && amount < 256);

		// unrolling
		if(shouldBeOptimized) {
			for(int idx = 0; idx < amount; idx++) {
				code << codeStmt.code;
			}
			return StmtInfo(code, codeStmt.stackalloc);
		}
	}

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

	if(from.typeId != TypeId(TInt)){
		throw std::runtime_error("Lower bound of for loop needs to be a integer expression.");
	}

	if(to.typeId != TypeId(TInt)){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}

	compPkg.getSymbolTable().addBlockScope();
	// iteration variable
	compPkg.getSymbolTable().insert(stmt.name, TypeId("int"));
	Var counter = compPkg.getSymbolTable().match(VarId(stmt.name));
	// create code inside loop
	StmtInfo body = codeBlock(compPkg, *stmt.stmt);
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