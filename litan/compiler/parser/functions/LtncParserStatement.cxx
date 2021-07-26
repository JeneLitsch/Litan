#include "LtncParserFunctions.hxx"


std::shared_ptr<ltnc::Stmt> ltnc::parse::statement(ParserPackage & parsePkg) {
	if(auto stmt = codeBlock(parsePkg)) return stmt;
	if(auto stmt = assembly(parsePkg)) return stmt;
	if(auto stmt = assign(parsePkg)) return stmt;
	if(auto stmt = ifElse(parsePkg)) return stmt;
	if(auto stmt = returnStmt(parsePkg)) return stmt;
	if(auto stmt = forLoop(parsePkg)) return stmt;
	if(auto stmt = whileLoop(parsePkg)) return stmt;
	if(auto stmt = repeatLoop(parsePkg)) return stmt;
	if(auto stmt = justAnExpression(parsePkg)) return stmt;
	return parsePkg.error("Expected statement");
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::justAnExpression(ParserPackage & parsePkg) {
	auto stmt = std::make_shared<StmtExpr>(expression(parsePkg));
	if (parsePkg.match(TokenType::SEMICOLON)) {
		return stmt;
	}
	return parsePkg.error("expected ;");
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::returnStmt(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::RETURN)) {
		// return void
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_shared<StmtReturn>(nullptr);
		}
		// return expression;
		auto expr = expression(parsePkg);
		auto stmt = std::make_shared<StmtReturn>(expr);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return stmt;
		}	
		return parsePkg.error("expected ; after return statement");
	}
	return nullptr;
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::assembly(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::ASM)){
		auto asmStmt = std::make_shared<StmtAsm>();
		if(parsePkg.match(TokenType::L_BRACE)){
			while(parsePkg.match(TokenType::STRING_LITERAL)) {
				asmStmt->instructions.push_back(parsePkg.prev().string);
			}
			if(parsePkg.match(TokenType::R_BRACE)){
				return asmStmt;
			}
			return parsePkg.error("Expected } after asm block");
		}
		return parsePkg.error("Expected { before asm block and after \"asm\" keyword");
	}
	return nullptr;
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::assign(ParserPackage & parsePkg) {
	if(auto exprVar = var(parsePkg)) {
		if (parsePkg.match(TokenType::ASSIGN)) {
			auto expr = expression(parsePkg);
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<StmtAssign>(exprVar, expr);
			}
			return parsePkg.error("assign: expected ;");
		}
		return parsePkg.error("expected =");
	}
	return nullptr;
}