#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Stmt> ltnc::parse::statement(ParserPackage & parsePkg) {
	if(auto stmt = codeBlock(parsePkg)) return stmt;
	if(auto stmt = assembly(parsePkg)) return stmt;
	if(auto stmt = assign(parsePkg)) return stmt;
	if(auto stmt = ifElse(parsePkg)) return stmt;
	if(parsePkg.match(TokenType::FOR)) return forLoop(parsePkg);
	if(parsePkg.match(TokenType::WHILE)) return whileLoop(parsePkg);
	if(parsePkg.match(TokenType::REPEAT)) return repeatLoop(parsePkg);

	if(parsePkg.match(TokenType::RETURN)) {
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_shared<StmtReturn>(nullptr);
		}
		auto expr = expression(parsePkg);
		auto stmt = std::make_shared<StmtReturn>(expr);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return stmt;
		}
		return parsePkg.error("expected ; after return statement");
	}
	auto stmt = std::make_shared<StmtExpr>(expression(parsePkg));
	if (parsePkg.match(TokenType::SEMICOLON)) {
		return stmt;
	}
	return parsePkg.error("expected ;");
}

std::shared_ptr<ltnc::StmtAsm> ltnc::parse::assembly(ParserPackage & parsePkg) {
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