#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Stmt> ltnc::parse::codeBlock(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::L_BRACE)){
		auto block = std::make_shared<StmtBlock>(parsePkg.prev().debugInfo);
		while(!parsePkg.match(TokenType::R_BRACE)) {
			auto stmt = statement(parsePkg);
			if(parsePkg.isAtEnd()) {
				throw error::expectedBraceR(parsePkg);
			}
			block->statements.push_back(stmt);
		}
		return block;
	}
	return nullptr;
}
