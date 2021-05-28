#include "LtncParserDeclFlt.hxx"

std::shared_ptr<ltnc::DeclVar> ltnc::ParserDeclFlt::eval(ParserPackage & parsePkg) const {
	if(parsePkg.match(TokenType::FLT)) {
		if(parsePkg.match(TokenType::IDENTIFIER)){
			std::string name = parsePkg.prev().string;
			if (parsePkg.match(TokenType::SEMICOLON)) {
				return std::make_shared<DeclVar>(name, Type::FLT);
			}
			return parsePkg.error("expected ;");
		}
		return parsePkg.error("expected identifier");
	}
	return nullptr;
}
