#include "LtncParserFunctions.hxx"


std::unique_ptr<ltn::c::Stmt> ltn::c::parse::statement(ParserPackage & parsePkg) {
	if(auto stmt = codeBlock(parsePkg)) return stmt;
	if(auto stmt = assembly(parsePkg)) return stmt;
	if(auto stmt = ifElse(parsePkg)) return stmt;
	if(auto stmt = returnStmt(parsePkg)) return stmt;
	if(auto stmt = forLoop(parsePkg)) return stmt;
	if(auto stmt = whileLoop(parsePkg)) return stmt;
	if(auto stmt = repeatLoop(parsePkg)) return stmt;
	if(auto stmt = declareVar(parsePkg)) return stmt;
	if(auto stmt = justAnExpression(parsePkg)) return stmt;
	throw error::expectedStatement(parsePkg);
}


std::unique_ptr<ltn::c::Stmt> ltn::c::parse::justAnExpression(ParserPackage & parsePkg) {
	auto expr = expression(parsePkg);
	if (parsePkg.match(TokenType::SEMICOLON)) {
		return std::make_unique<StmtExpr>(expr->debugInfo, std::move(expr));
	}
	throw error::expectedSemicolon(parsePkg);
}


std::unique_ptr<ltn::c::Stmt> ltn::c::parse::returnStmt(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::RETURN)) {
		const auto & debugInto = parsePkg.prev().debugInfo;
		// return void
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_unique<StmtReturn>(debugInto, nullptr);
		}
		// return expression;
		auto expr = expression(parsePkg);
		if (parsePkg.match(TokenType::SEMICOLON)) {
			return std::make_unique<StmtReturn>(debugInto, std::move(expr));
		}	
		throw error::expectedSemicolon(parsePkg);
	}
	return nullptr;
}


std::unique_ptr<ltn::c::Stmt> ltn::c::parse::assembly(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::ASM)){
		auto debugInfo = parsePkg.prev().debugInfo;
		auto asmStmt = std::make_unique<StmtAsm>(debugInfo);
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


