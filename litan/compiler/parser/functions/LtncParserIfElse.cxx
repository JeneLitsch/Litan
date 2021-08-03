#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Stmt> ltnc::parse::ifElse(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::IF)) {
		std::shared_ptr<Expr> condition;
		std::shared_ptr<Stmt> stmtIf;
		std::shared_ptr<Stmt> stmtElse;
		if(parsePkg.match(TokenType::L_PAREN)) {
			condition = expression(parsePkg);
			if(parsePkg.match(TokenType::R_PAREN)) {
				stmtIf = statement(parsePkg);
				if(parsePkg.match(TokenType::ELSE)) {
					stmtElse = statement(parsePkg);
				}
			}
		}
		if(!condition) {
			throw error::missingCondition(parsePkg);
		}
		if(!stmtIf) {
			throw error::missingIfBranch(parsePkg);
		}
		auto ifElse = std::make_shared<StmtIf>();
		ifElse->stmtIf = stmtIf;
		ifElse->stmtElse = stmtElse;
		ifElse->condition = condition;
		return ifElse;
	}
	return nullptr;
}
