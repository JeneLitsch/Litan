#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::Stmt> ltnc::parse::forLoop(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::FOR)) {
		auto loop = std::make_shared<StmtFor>();
		if(parsePkg.match(TokenType::L_PAREN)) {
			if(parsePkg.match(TokenType::IDENTIFIER)) {
				loop->name = parsePkg.prev().string;
				if(parsePkg.match(TokenType::COMMA)) {
					loop->exprFrom = expression(parsePkg);
					if(parsePkg.match(TokenType::COMMA)){
						loop->exprTo = expression(parsePkg);
						if(parsePkg.match(TokenType::R_PAREN)){
							if(auto block = codeBlock(parsePkg)){
								loop->stmt = block;
								return loop;
							}
							return parsePkg.error("expected block statement");
						}
						return parsePkg.error("expected )");
					}
					return parsePkg.error("expected ,");
				}
				return parsePkg.error("expected ,");
			}
			return parsePkg.error("expected identfier");
		}
		return parsePkg.error("expected (");
	}
	return nullptr;
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::repeatLoop(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::REPEAT)) {
		auto loop = std::make_shared<StmtRepeat>();
		if(parsePkg.match(TokenType::L_PAREN)) {
			loop->expr = expression(parsePkg);
			if(parsePkg.match(TokenType::R_PAREN)){
				if(auto block = codeBlock(parsePkg)){
					loop->stmt = block;
					return loop;
				}
				return parsePkg.error("expected block statement");
			}
			return parsePkg.error("expected )");
		}
		return parsePkg.error("expected (");
	}
	return nullptr;
}


std::shared_ptr<ltnc::Stmt> ltnc::parse::whileLoop(ParserPackage & parsePkg) {
	if(parsePkg.match(TokenType::WHILE)) {
		auto loop = std::make_shared<StmtWhile>();
		if(parsePkg.match(TokenType::L_PAREN)) {
			loop->expr = expression(parsePkg);
			if(parsePkg.match(TokenType::R_PAREN)) {
				if(auto block = codeBlock(parsePkg)) {
					loop->stmt = block;
					return loop;
				}
				return parsePkg.error("expected {");
			}
			return parsePkg.error("expected )");
		}
		return parsePkg.error("Invalid while loop");
	}
	return nullptr;
}