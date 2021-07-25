#include "LtncParserFunctions.hxx"

std::shared_ptr<ltnc::StmtFor> ltnc::parse::forLoop(ParserPackage & parsePkg) {
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


std::shared_ptr<ltnc::StmtRepeat> ltnc::parse::repeatLoop(ParserPackage & parsePkg) {
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


std::shared_ptr<ltnc::StmtWhile> ltnc::parse::whileLoop(ParserPackage & parsePkg) {
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