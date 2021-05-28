#include "LtncParserBlock.hxx"


void ltnc::ParserBlock::connect(
	const ParserNode<Stmt> & stmt,
	const ParserNode<DeclVar> & declInt,
	const ParserNode<DeclVar> & declFlt) {
	
	this->stmt = &stmt;
	this->declInt = &declInt;
	this->declFlt = &declFlt;
}

std::shared_ptr<ltnc::StmtBlock> ltnc::ParserBlock::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::L_BRACE)){
		auto block = std::make_shared<StmtBlock>();
		while(!parsePkg.match(TokenType::R_BRACE)) {

			if(auto decl = this->declInt->eval(parsePkg)) {
				block->declarations.push_back(decl);
			}
			else if(auto decl = this->declFlt->eval(parsePkg)) {
				block->declarations.push_back(decl);
			}
			else if(parsePkg.match(TokenType::VOI)) throw std::runtime_error("Variables of type voi/void are not allowed.");
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
