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
	throw error::expectedStatement(parsePkg);
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::justAnExpression(ParserPackage & parsePkg) {
	auto stmt = std::make_shared<StmtExpr>(expression(parsePkg));
	if (parsePkg.match(TokenType::SEMICOLON)) {
		return stmt;
	}
	throw error::expectedSemicolon(parsePkg);
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
		throw error::expectedSemicolon(parsePkg);
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
			throw error::unclosedAsm(parsePkg);
		}
		throw error::unopenedAsm(parsePkg);
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
			throw error::expectedSemicolon(parsePkg);
		}
		throw error::expectedEqual(parsePkg);
	}
	return nullptr;
}