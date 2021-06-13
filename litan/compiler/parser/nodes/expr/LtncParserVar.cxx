#include "LtncParserVar.hxx"
#include <iostream>
std::shared_ptr<ltnc::ExprVar> ltnc::ParserVar::eval(ParserPackage & parsePkg) const {
	// variables and constants
	if (parsePkg.match(TokenType::IDENTIFIER)) {
		auto exprVar = std::make_shared<ExprVar>(parsePkg.prev().string);
		while(parsePkg.match(TokenType::DOT)) {
			if (!parsePkg.match(TokenType::IDENTIFIER)) {
				return parsePkg.error("expected identifier after .");
			}
			exprVar->path.push_back(parsePkg.prev().string);
		}
		return exprVar;
	}
	return nullptr;
}
