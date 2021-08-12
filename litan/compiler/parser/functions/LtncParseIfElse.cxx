#include "LtncParserFunctions.hxx"

std::unique_ptr<ltnc::Stmt> ltnc::parse::ifElse(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::IF)) {
		auto ifElse = std::make_unique<StmtIf>(parsePkg.prev().debugInfo);
		if(parsePkg.match(TokenType::L_PAREN)) {
			ifElse->condition = expression(parsePkg);
			if(parsePkg.match(TokenType::R_PAREN)) {
				ifElse->stmtIf = statement(parsePkg);
				if(parsePkg.match(TokenType::ELSE)) {
					ifElse->stmtElse = statement(parsePkg);
				}
			}
		}
		if(!ifElse->condition) {
			throw error::missingCondition(parsePkg);
		}
		if(!ifElse->stmtIf) {
			throw error::missingIfBranch(parsePkg);
		}
		return ifElse;
	}
	return nullptr;
}
