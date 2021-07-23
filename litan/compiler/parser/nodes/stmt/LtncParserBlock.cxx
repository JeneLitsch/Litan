#include "LtncParserBlock.hxx"


ltnc::ParserBlock::ParserBlock(
	const ParserNode<Stmt> & stmt,
	const ParserNode<DeclVar> & declVar) {
	
	this->stmt = &stmt;
	this->declVar = &declVar;
}

std::shared_ptr<ltnc::StmtBlock> ltnc::ParserBlock::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::L_BRACE)){
		auto block = std::make_shared<StmtBlock>();
		while(!parsePkg.match(TokenType::R_BRACE)) {

			if(auto decl = this->declVar->eval(parsePkg)) {
				block->declarations.push_back(decl);
				if(decl->assign) {
					block->statements.push_back(decl->assign);
				}
			}
			else {
				auto stmt = this->stmt->eval(parsePkg);
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
