#include "LtncStmtCompiler.hxx"
#include <iostream>
#include <sstream>

ltnc::StmtInfo ltnc::StmtCompiler::compile(CompilerPack & compPkg, const std::shared_ptr<Stmt> & stmt) const {
	return this->compileStmt(compPkg, stmt);
}

ltnc::StmtInfo ltnc::StmtCompiler::compileStmt(CompilerPack & compPkg, std::shared_ptr<Stmt> stmt) const {
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtAssign>(stmt)) {
		return this->compileAssign(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtBlock>(stmt)) {
		return this->compileBlock(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtIf>(stmt)) {
		return this->compileIf(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtFor>(stmt)) {
		return this->compileFor(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtRepeat>(stmt)) {
		return this->compileRepeat(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtWhile>(stmt)) {
		return this->compileWhile(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtExpr>(stmt)) {
		return this->compileEval(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtReturn>(stmt)) {
		return this->compileReturn(compPkg, stmt_);
	}
	if(auto stmt_ = std::dynamic_pointer_cast<ltnc::StmtAsm>(stmt)) {
		return StmtInfo(this->asmbCompiler.compile(compPkg, stmt_), 0);
	}
	return StmtInfo("",0);
}



ltnc::StmtInfo ltnc::StmtCompiler::compileAssign(CompilerPack & compPkg, std::shared_ptr<StmtAssign> stmt) const {
	auto expr = exprCompiler.compileExpr(compPkg, stmt->expr);
	auto access = this->exprCompiler.compileAccess(compPkg, stmt->var, expr);
		CodeBuffer code = compPkg.codeBuffer();
		if(expr.type != access.type.name) throw std::runtime_error("Types do not match: " + expr.code.str());
		code << access.code;
		return StmtInfo(code, 0);

	// stack
	if(stmt->var->path.size() == 1) {
		CodeBuffer code = compPkg.codeBuffer();
		Var var = compPkg.getScopes().get().getVar(stmt->var->path[0]);

		if(expr.type != var.typeName) throw std::runtime_error("Types do not match: " + expr.code.str());

		code << Comment("assign to int var " + stmt->var->path[0]); 
		code << expr.code;
		code << Inst::store(var.addr);
		return StmtInfo(code, 0);
	}

	// heap
	else {

	}
}

ltnc::StmtInfo ltnc::StmtCompiler::compileRepeat(CompilerPack & compPkg, std::shared_ptr<StmtRepeat> stmt) const {
	
	CodeBuffer code = compPkg.codeBuffer();
	// From and to expression
	ExprInfo expr = this->exprCompiler.compileExpr(compPkg, stmt->expr); 


	if(expr.type != "int"){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}
	
	compPkg.getScopes().addBlockScope();
	// iteration variable
	// create code inside loop
	StmtInfo codeStmt = this->compileBlock(compPkg, stmt->stmt);
	compPkg.getScopes().remove();

	// unroll repeat
	if(expr.constant) {
		std::int64_t amount = std::get<std::int64_t>(expr.constant->value);
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

ltnc::StmtInfo ltnc::StmtCompiler::compileFor(CompilerPack & compPkg, std::shared_ptr<StmtFor> stmt) const {
	// From and to expression
	ExprInfo from = this->exprCompiler.compileExpr(compPkg, stmt->exprFrom); 
	ExprInfo to = this->exprCompiler.compileExpr(compPkg, stmt->exprTo);

	if(from.type != "int"){
		throw std::runtime_error("Lower bound of for loop needs to be a integer expression.");
	}

	if(to.type != "int"){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}

	compPkg.getScopes().addBlockScope();
	// iteration variable
	Var counter = compPkg.getScopes().get().registerVar(stmt->name, Type("int"));
	// create code inside loop
	StmtInfo body = this->compileBlock(compPkg, stmt->stmt);
	compPkg.getScopes().remove();

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


ltnc::StmtInfo ltnc::StmtCompiler::compileWhile(CompilerPack & compPkg, std::shared_ptr<StmtWhile> stmt) const {
	auto codeExpr = this->exprCompiler.compileExpr(compPkg, stmt->expr); 
	auto codeStmt = this->compileStmt(compPkg, stmt->stmt);
	auto endMark = compPkg.makeJumpMark("LOOP_END");
	auto loopMark = compPkg.makeJumpMark("LOOP");
	
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

ltnc::StmtInfo ltnc::StmtCompiler::compileBlock(CompilerPack & compPkg, std::shared_ptr<StmtBlock> block) const {
	compPkg.getScopes().addBlockScope();
	CodeBuffer code = compPkg.codeBuffer();
	for(const auto & decl : block->declarations) {
		compPkg.getTypeTable().guardType(decl->type.name);
		Var var = compPkg.getScopes().get().registerVar(decl->name, decl->type);
	}
	unsigned stackalloc = 0;
	for(const auto & stmt : block->statements) {
		StmtInfo stmtInfo = this->compileStmt(compPkg, stmt);
		stackalloc = std::max<unsigned>(stackalloc, stmtInfo.stackalloc);
		code << stmtInfo.code;
	}
	stackalloc += block->declarations.size();
	compPkg.getScopes().remove();
	return StmtInfo(code, stackalloc);
}



ltnc::StmtInfo ltnc::StmtCompiler::compileIf(CompilerPack & compPkg, std::shared_ptr<StmtIf> stmt) const {
	CodeBuffer code = compPkg.codeBuffer();

	// make jump marks
	std::string jmIf = compPkg.makeJumpMark("IF");
	std::string jmElse = compPkg.makeJumpMark("ELSE");
	std::string jmEnd = compPkg.makeJumpMark("END_IF");
	

	ExprInfo condition = this->exprCompiler.compileExpr(compPkg, stmt->condition);
	StmtInfo codeIf = this->compileStmt(compPkg, stmt->stmtIf);
	unsigned stackalloc;

	if(stmt->stmtElse) {
		StmtInfo codeElse = this->compileStmt(compPkg, stmt->stmtElse);
		stackalloc = std::max<unsigned>(codeIf.stackalloc, codeElse.stackalloc);
		
		code << condition.code;
		code << AssemblyCode("ifnx");
		code << AssemblyCode("goto " + jmIf);
		code << AssemblyCode("goto " + jmElse);
		
		code << AssemblyCode("-> " + jmIf);
		code << codeIf.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmElse);
		code << codeElse.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmEnd);		
	}

	else {
		stackalloc = codeIf.stackalloc;
		code << condition.code;
		code << AssemblyCode("ifnx");
		code << AssemblyCode("goto " + jmIf);
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmIf);
		code << codeIf.code;
		code << AssemblyCode("goto " + jmEnd);
		
		code << AssemblyCode("-> " + jmEnd);
	}
	return StmtInfo(code, stackalloc);
}



ltnc::StmtInfo ltnc::StmtCompiler::compileEval(CompilerPack & compPkg, std::shared_ptr<StmtExpr> stmt) const {
	ExprInfo exprInfo = this->exprCompiler.compileExpr(compPkg, stmt->expr);
	CodeBuffer code = compPkg.codeBuffer();
	code << exprInfo.code;
	if(exprInfo.type != "voi") {
		code << "scrap";
	}
	return StmtInfo(code, 0);
}

ltnc::StmtInfo ltnc::StmtCompiler::compileReturn(CompilerPack & compPkg, std::shared_ptr<StmtReturn> stmt) const {
	CodeBuffer code = compPkg.codeBuffer();
	FxSignature signature = compPkg.getScopes().get().getFxSignature();
	if(stmt->expr) {
		ExprInfo exprInfo = this->exprCompiler.compileExpr(compPkg, stmt->expr);
		if(exprInfo.type != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
		code << exprInfo.code; 
	}
	else {
		if("voi" != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
	}
	code << AssemblyCode("return");
	return StmtInfo(code, 0);
}

