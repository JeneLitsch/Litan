#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::StmtBlock> ltnc::parse::codeBlock(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::L_BRACE)){
		auto block = std::make_shared<StmtBlock>();
		while(!parsePkg.match(TokenType::R_BRACE)) {

			if(auto decl = declareVar(parsePkg)) {
				block->declarations.push_back(decl);
				if(decl->assign) {
					block->statements.push_back(decl->assign);
				}
			}
			else {
				auto stmt = statement(parsePkg);
				if(parsePkg.isAtEnd()) {
					return parsePkg.error("No closing }");
				}
				block->statements.push_back(stmt);
			}

		}
		return block;
	}
	return nullptr;
}
