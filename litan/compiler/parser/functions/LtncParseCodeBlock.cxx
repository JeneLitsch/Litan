#include "LtncParserFunctions.hxx"

std::unique_ptr<ltn::c::Stmt> ltn::c::parse::codeBlock(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::L_BRACE)){
		auto block = std::make_unique<StmtBlock>(parsePkg.prev().debugInfo);
		while(!parsePkg.match(TokenType::R_BRACE)) {
			auto stmt = statement(parsePkg);
			if(parsePkg.isAtEnd()) {
				throw error::expectedBraceR(parsePkg);
			}
			block->statements.push_back(std::move(stmt));
		}
		return block;
	}
	return nullptr;
}
