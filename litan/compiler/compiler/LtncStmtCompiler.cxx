#include "LtncStmtCompiler.hxx"
#include <iostream>

std::string ltnc::StmtCompiler::compileProgram(CompilerPack & compPkg, std::shared_ptr<Program> program){
	compPkg.getScopes().addFunctionScope(FxSignature(Type::VOI, "", {}));
	for(const auto & function : program->functions) {
		compPkg.registerFunction(function);
	}
	std::string code;
	code += "-> MAIN \n"; 
	code += this->compileEval(compPkg, std::make_shared<StmtExpr>(std::make_shared<ExprCall>("main")));
	code += "exit \n";
	code += "\n\n";
	for(const auto & function : program->functions) {
		code += this->compileFunction(compPkg, function);
	}
	
	return code;
}

std::string ltnc::StmtCompiler::compileStmt(CompilerPack & compPkg, std::shared_ptr<Stmt> stmt){
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
		return this->asmBlock.compile(compPkg, stmt_);
	}
	return "";
}



std::string ltnc::StmtCompiler::compileAssign(CompilerPack & compPkg, std::shared_ptr<StmtAssign> stmt){
	auto expr = exprCompiler.compileExpr(compPkg, stmt->expr);
	
	Var var = compPkg.getScopes().get().getVar(stmt->name);

	if(expr.type != var.type) throw std::runtime_error("Types do not match: " + expr.code);

	return this->comment(compPkg, "assign to int var " + stmt->name) + expr.code
		+ "store " + std::to_string(var.addr) + "\n";
}

std::string ltnc::StmtCompiler::compileRepeat(CompilerPack & compPkg, std::shared_ptr<StmtRepeat> stmt) {
	// From and to expression
	ExprInfo expr = this->exprCompiler.compileExpr(compPkg, stmt->expr); 


	if(expr.type != Type::INT){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}
	
	compPkg.getScopes().addBlockScope();
	// iteration variable
	// create code inside loop
	std::string codeStmt = this->compileBlock(compPkg, stmt->stmt);
	compPkg.getScopes().remove();

	// unroll repeat
	if(expr.constant) {
		std::int64_t amount = std::get<std::int64_t>(expr.constant->value);
		if(amount <= 0) {
			std::cout << ">> [Warning] repeat loop: needs to be bigger than 0" << std::endl;
		}

		std::string code;
		bool shouldBeOptimized =
			(compPkg.getSettings().getOptimizationLevel() == 1 && amount < 64) ||
			(compPkg.getSettings().getOptimizationLevel() == 2 && amount < 128) ||
			(compPkg.getSettings().getOptimizationLevel() >= 3 && amount < 256);

		// unrolling
		if(shouldBeOptimized) {
			for(int idx = 0; idx <= amount; idx++) {
				code += codeStmt;
			}
			return code;
		}
	}


	// create code
	return 
		"newi 0\n" +
		expr.code +
		"loop::range \n" +
		"loop::idx \n" +
		codeStmt +
		"loop::cont \n";
}

std::string ltnc::StmtCompiler::compileFor(CompilerPack & compPkg, std::shared_ptr<StmtFor> stmt) {
	// From and to expression
	ExprInfo from = this->exprCompiler.compileExpr(compPkg, stmt->exprFrom); 
	ExprInfo to = this->exprCompiler.compileExpr(compPkg, stmt->exprTo);

	if(from.type != Type::INT){
		throw std::runtime_error("Lower bound of for loop needs to be a integer expression.");
	}

	if(to.type != Type::INT){
		throw std::runtime_error("Upper bound of for loop needs to be a integer expression.");
	}

	compPkg.getScopes().addBlockScope();
	// iteration variable
	Var counter = compPkg.getScopes().get().registerVar(stmt->name, Type::INT);
	// create code inside loop
	std::string codeStmt = this->compileBlock(compPkg, stmt->stmt);
	compPkg.getScopes().remove();

	return 
		from.code +
		to.code +
		"loop::range \n" +
		"loop::idx \n" +
		"store " + std::to_string(counter.addr) + "\n" +
		codeStmt +
		"loop::cont \n";
}


std::string ltnc::StmtCompiler::compileWhile(CompilerPack & compPkg, std::shared_ptr<StmtWhile> stmt) {
	auto codeExpr = this->exprCompiler.compileExpr(compPkg, stmt->expr); 
	auto codeStmt = this->compileStmt(compPkg, stmt->stmt);
	auto endMark = compPkg.makeJumpMark("LOOP_END");
	auto loopMark = compPkg.makeJumpMark("LOOP");
	return 
		"-> " + loopMark + "\n" +
		codeExpr.code +
		"ifnot\n" +
		"goto " + endMark + "\n" +
		codeStmt +
		"goto " + loopMark + "\n" +
		"-> " + endMark + "\n";
}

std::string ltnc::StmtCompiler::compileBlock(CompilerPack & compPkg, std::shared_ptr<StmtBlock> block) {
	compPkg.getScopes().addBlockScope();
	std::string code;
	for(const auto & decl : block->declarations) {
		Var var = compPkg.getScopes().get().registerVar(decl->name, decl->type);
	}
	for(const auto & stmt : block->statements) {
		code+= this->compileStmt(compPkg, stmt);
	}
	compPkg.getScopes().remove();
	return code;
}



std::string ltnc::StmtCompiler::compileIf(CompilerPack & compPkg, std::shared_ptr<StmtIf> stmt) {

	// make jump marks
	std::string jmIf = compPkg.makeJumpMark("IF");
	std::string jmElse = compPkg.makeJumpMark("ELSE");
	std::string jmEnd = compPkg.makeJumpMark("END_IF");
	

	std::string condition = this->exprCompiler.compileExpr(compPkg, stmt->condition).code;
	std::string codeIf = this->compileStmt(compPkg, stmt->stmtIf);
	

	if(stmt->stmtElse) {
		std::string codeElse = this->compileStmt(compPkg, stmt->stmtElse);
		return
			condition +
			"ifnx" + "\n" +
			"goto " + jmIf + "\n" +
			"goto " + jmElse + "\n" +
			"-> " + jmIf + "\n" +
			codeIf +
			"goto " + jmEnd + "\n" +
			
			"-> " + jmElse + "\n" +
			codeElse +
			"goto " + jmEnd + "\n" +
			
			"-> " + jmEnd + "\n";
	}
	else {
		return
			condition +
			"ifnx" + "\n" +
			"goto " + jmIf + "\n" +
			"goto " + jmEnd + "\n" +
			
			"-> " + jmIf + "\n" +
			codeIf +
			"-> " + jmEnd + "\n";
	}
}

std::string ltnc::StmtCompiler::compileFunction(CompilerPack & compPkg, std::shared_ptr<DeclFunction> decl) {
	FxInfo fxInfo = *compPkg.matchFunction(decl->signature);

	compPkg.getScopes().addFunctionScope(fxInfo.signature);
	// register parameter
	for(const Param & param : decl->signature.params) {
		compPkg.getScopes().get().registerVar(param.name, param.type);
	}
	// eval body
	std::string bodyCode = this->compileStmt(compPkg, decl->body);

	// create code;
	std::string code;
	code += this->comment(compPkg, decl->signature.name + " " + std::to_string(decl->signature.params.size()) + " -> " + std::to_string(static_cast<int>(decl->signature.returnType.type)));
	code += "-> " + fxInfo.jumpMark + "\n";
	// load params into memory (backwards because LIFO)
	for(auto param = decl->signature.params.rbegin(); param != decl->signature.params.rend(); ++param) {
		// store parameter;
		std::uint64_t varAddr = compPkg.getScopes().get().getVar((*param).name).addr;
		code += "store " + std::to_string(varAddr) + "\n";
	}
	code += "stackalloc 64\n";
	code += bodyCode;
	compPkg.getScopes().remove();
	return code + "\n\n";
}

std::string ltnc::StmtCompiler::compileEval(CompilerPack & compPkg, std::shared_ptr<StmtExpr> stmt) {
	ExprInfo exprInfo = this->exprCompiler.compileExpr(compPkg, stmt->expr);
	std::string code;
	code += exprInfo.code;
	if(exprInfo.type == Type::INT || exprInfo.type == Type::FLT) {
		code += "scrap \n";
	}
	return code;
}

std::string ltnc::StmtCompiler::compileReturn(CompilerPack & compPkg, std::shared_ptr<StmtReturn> stmt) {
	std::string code = "";
	FxSignature signature = compPkg.getScopes().get().getFxSignature();
	if(stmt->expr) {
		ExprInfo exprInfo = this->exprCompiler.compileExpr(compPkg, stmt->expr);
		if(exprInfo.type != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
		code += exprInfo.code; 
	}
	else {
		if(Type::VOI != signature.returnType) {
			throw std::runtime_error("Type of return statement do not match return type of function");
		}
	}
	code += "return \n";
	return code;
}

